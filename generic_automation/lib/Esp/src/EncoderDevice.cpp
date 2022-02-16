#include "../include/EncoderDevice.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include <stdint.h>

using namespace genauto;

unsigned long lastTime = 0;

/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 *
 * @param pinNumber
 */
genauto::EncoderDevice::EncoderDevice(uint8_t pinNumber /*, uint8_t minorId*/)
    : pinNumber(pinNumber)
// will need to add "minorId(MinorId)"
{
    pinMode(pinNumber, INPUT);
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
        if (digitalRead(pinNumber))
        {
            pressed_ = true;
        }
    }
}

/**
 * @brief
 *
 * @return Message*
 */
Message *tryGet()
{
    if (pressed_)
    {
        pressed_ = false;
        EncoderMessage* bMsg = EncoderMessage::EncoderMessage(void);
        bMsg->pressed() = true;
        return bMsg
    }
}