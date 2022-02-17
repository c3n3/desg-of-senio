#include "../include/ButtonDevice.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include <stdint.h>

using namespace genauto;

static 

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


void IRAM_ATTR handleButtonInterrupt_1()
{
    
}

/**
 * @brief
 *
 */
void genauto::ButtonDevice::execute()
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
        ButtonMessage* bMsg = ButtonMessage::ButtonMessage(void);
        bMsg->pressed() = true;
        return bMsg
    }
}