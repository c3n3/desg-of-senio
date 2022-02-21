#include "../include/EncoderDevice.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include <stdint.h>
#include <ESP32Encoder.h>

using namespace genauto;


/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 *
 * @param pinNumber
 */
genauto::EncoderDevice::EncoderDevice(uint8_t pinA, uint8_t pinB, minor_t minorId)
    : pinA(pinA),
    pinB(pinB),
    Device(minorId)
{
    ESP32Encoder::useInternalWeakPullResistors=UP;
	encoder.attachHalfQuad(pinA, pinB);
    encoder.clearCount();
	lastTime = millis();
}

/**
 * @brief
 *
 */
void genauto::EncoderDevice::execute()
{
    if ((millis() - lastTime) >= 250)
    {
        lastTime = millis();
        if(count != encoder.getCount())
        {
            count = encoder.getCount();
            flag = true;
        }
        eMsg->value() = count;
    }
}

/// As of right now, this class does not implement a Queue for encoder messages,
/// this shouldn't be a problem, but if it becomes a problem, we can implement
/// a Queue.


/**
 * @brief
 *
 * @return Message*
 */
Message *genauto::EncoderDevice::tryGet()
{
    if (flag)
    {
        flag = false;
        EncoderMessage *eMsg = EncoderMessage(NULL);
        return eMsg;
    }
}