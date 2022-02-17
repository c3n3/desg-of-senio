#include "../include/AnalogDevice.hpp"
#include "../../Common/include/AnalogMessage.hpp"
#include <stdint.h>

using namespace genauto;

unsigned long lastTime = 0;
unsigned long readTime = 0;
int16_t accumValue = 0  // sum of the values read in during ~ 250ms interval.
uint8_t count = 0; // number of values summed into accumValue

/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 *
 * @param pinNumber
 */
genauto::AnalogDevice::AnalogDevice(uint8_t pinNumber /*, uint8_t minorId*/)
    : pinNumber(pinNumber)
// will need to add "minorId(MinorId)"
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
    if (millis() - readTime >= 10) // read these values more often, and filter 
    {
        accumValue += analogRead(analogReadPin);
        count++;
        if ((millis() - lastTime) >= 250)
        {
            lastTime = millis();
            flag = true;
            value = accumValue / count;
            accumValue = 0;
            count = 0;
        }
    }
}

/**
 * @brief called to return a message pointer containing the information acquired in the execute() function.
 *
 * @return Message*
 */
Message *tryGet()
{
    if (flag)
    {
        flag = false;
        AnalogMessage *aMsg = AnalogMessage::AnalogMessage(void);
        aMsg->value() = value;
        return bMsg
    }
}