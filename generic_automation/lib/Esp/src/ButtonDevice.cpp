#include "../include/ButtonDevice.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include <stdint.h>

using namespace genauto;


/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 *
 * @param pinNumber
 */
genauto::ButtonDevice::ButtonDevice(uint8_t pinNumber /*, uint8_t minorId*/)
    : pinNumber(pinNumber)
// will need to add "minorId(MinorId)"
{
    pinMode(pinNumber, INPUT);
}


/**
 * @brief
 *
 */
void genauto::ButtonDevice::execute()
{
    if ((millis() - lastTime) >= 250)
    {
        if(pressed_)
        {
            bMsg->pressed();
            lastTime = millis();
            pressed_ = false;
            send = true;
        }
    }
}

/**
 * @brief
 *
 * @return Message*
 */
Message *genauto::ButtonDevice::tryGet()
{
    if (send)
    {
        send = false;
        return bMsg;
    }
}