#include "../include/EncoderDevice.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include <stdint.h>
#include <ESP32Encoder.h>

using namespace genauto;

unsigned long lastTime = 0;
ESP32Encoder encoder;

/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 *
 * @param pinNumber
 */
genauto::EncoderDevice::EncoderDevice(uint8_t pinA, uint8_t pinB /*, uint8_t minorId*/)
    : pinA(pinA),
    pinB(pinB)
// will need to add "minorId(MinorId)"
{
    ESP32Encoder::useInternalWeakPullResistors=UP;
	encoder.attachHalfQuad(pinA, pinB);
    encoder2.clearCount();
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
        count = encoder2.getCount()
        flag = true;
    }
}

/**
 * @brief
 *
 * @return Message*
 */
Message *tryGet()
{
    if (flag)
    {
        flag = false;
        EncoderMessage* eMsg = EncoderMessage::EncoderMessage(void);
        eMsg->value() = count;
        return bMsg
    }
}