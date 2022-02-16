#include "../include/AnalogDevice.hpp"
#include "../../Common/include/AnalogMessage.hpp"
#include <stdint.h>

using namespace genauto;

unsigned long lastTime = 0;

/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 *
 * @param pinNumber
 */
genauto::AnalogDevice::AnalogDevice(uint8_t pinNumber /*, uint8_t minorId*/)
    : pinNumber(pinNumber)
// will need to add "minorId(MinorId)"
{
    
}

/**
 * @brief
 *
 */
void genauto::AnalogDevice::execute()
{
    if ((millis() - lastTime) >= 250)
    {
        lastTime = millis();
        value = analogRead(analogReadPin);
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
        AnalogMessage* aMsg = AnalogMessage::AnalogMessage(void);
        aMsg->value() = value;
        return bMsg
    }
}