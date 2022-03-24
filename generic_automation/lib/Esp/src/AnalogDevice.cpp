#include "../include/AnalogDevice.hpp"
#include "../../Common/include/AnalogMessage.hpp"
#include "../../Common/include/Device.hpp"
#include <stdint.h>

using namespace genauto;

/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 *
 * @param pinNumber
 */
genauto::AnalogDevice::AnalogDevice(uint8_t pinNumber, minor_t minorId)
    : pinNumber(pinNumber),
    Device(minorId)
{
    lastTime = millis();
    readTime = lastTime;
}

/**
 * @brief the function that will be called every cycle of the main loop.
 *          Reads in values for the analog device and filters values for a more
 *          accurate representation of the last ~ 250ms and stores that average
 *          in the value variable.
 */
void genauto::AnalogDevice::execute()
{
    if (millis() - readTime >= 100) // read these values more often, and filter
    {
        //delay(10);
        //dlog("analogRead(): \n"); // for some reason when I comment this line out, the values go crazy, wtf
        uint16_t aRead;
        aRead = analogRead(pinNumber);
        //dlog("analogRead(): %d\n", aRead);
        accumValue += aRead;
        count++;
        readTime = millis(); // wasn't updating the readTime so it was going into the wrapping if () statement every cycle so it was reading hella fast
        if ((millis() - lastTime) >= 500)
        {
            lastTime = millis();
            flag = true;
            value = accumValue / count;
            //dlog("HERE %d\n", value);
            accumValue = 0;
            count = 0;
            
            if(true) // change this to if(thermistor)
            {
                
                float resistor = 9907.0; // test my resistor, see if its maybe off by 20%`
                float Vi = 3.3/4095.0 * (float)value;
                Vi += 0.1; // voltage correction factor
                //dlog("value: %d\n", (int)value);
                uint32_t resistance = Vi * resistor / (3.3 - Vi);
                // resistor values from kty81-210 data sheet, written as polynomial trend line
                float temp = 1.02192985237609e-03 + 1.65394923419592e-07 * pow(log(resistance),3) - 2.47620754758454e-07 * pow(log(resistance),2) + 2.41453242427025e-04 * log(resistance);
                temp = 1/temp;
                temp -= 273.15; // K to C
                value = temp * 1.8 + 32; // C to F
                //dlog("resistance: %d\n", resistance); // this for testing purposes
            }
        }
    }
}

/**
 * @brief called to return a message pointer containing the information acquired in the execute() function.
 *
 * @return Message*
 */
Message *genauto::AnalogDevice::tryGet()
{
    if (flag)
    {
        flag = false;
        aMsg.value() = value;
        return &aMsg;
    }
    return nullptr;
}