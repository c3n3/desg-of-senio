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
    Device(minorId), timeRise_(0)
{
    pinMode(pinNumber, INPUT);
}


/**
 * @brief
 *
 */
void genauto::ButtonDevice::execute()
{
    if (!inited) {
        bMsg.id() = MessageId(deviceId, minorId);
        inited = true;
    }
    uint32_t res = millis() - timeRise_;
    if(timeRise_ != 0 && res > 100 && millis() - lastTime > 500)
    {
        dlog("Time rise = %u, last time = %u\n", res, lastTime);
        timeRise_ = 0;
        lastTime = millis();
        bMsg.pressed() = true;
        pressed_ = false;
        send = true;
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

Publisher* genauto::ButtonDevice::pub()
{
    return static_cast<Publisher*>(this);
}
