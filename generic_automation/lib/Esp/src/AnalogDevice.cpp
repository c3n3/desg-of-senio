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
    if (millis() - readTime >= 10) // read these values more often, and filter
    {
        accumValue += analogRead(pinNumber);
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
Message *genauto::AnalogDevice::tryGet()
{
    if (flag)
    {
        flag = false;
        AnalogMessage *aMsg = AnalogMessage(NULL);
        aMsg->value() = value;
        return aMsg;
    }
}