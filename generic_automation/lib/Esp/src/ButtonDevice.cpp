#include "../include/ButtonDevice.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include "../../Common/include/MessageId.hpp"
#include "../../Common/include/Device.hpp"
#include <stdint.h>

using namespace genauto;


/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 *
 * @param pinNumber
 */
genauto::ButtonDevice::ButtonDevice(uint8_t pinNumber, minor_t minorId)
    : pinNumber(pinNumber),
    Device(minorId)
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
            bMsg.pressed() = true;
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
        return &bMsg;
    }
    return nullptr;
}