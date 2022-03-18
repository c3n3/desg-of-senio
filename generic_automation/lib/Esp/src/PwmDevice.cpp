#include "../include/PwmDevice.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include "../../Common/include/PwmMessage.hpp"
#include <stdint.h>

static const uint16_t PWM_FREQUENCY = 5000;
static const uint8_t PWM_RESOUTION = 8;

using namespace genauto;

/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 * 
 * @param pinNumber 
 */
genauto::PwmDevice::PwmDevice(uint8_t pinNumber, uint8_t channel, minor_t minorId)  
    : pinNumber(pinNumber),
    channel(channel),
    Subscriber(),
    Device(minorId),
    inited(false)
{
}


int16_t PwmDevice::getDutyCycle()
{
    return dutyCycle_;
}


void PwmDevice::setDutyCycle(int16_t dutyCycle)
{
    dutyCycle_ = dutyCycle;
}


bool PwmDevice::getOnStatus()
{
    return pwmOn_;
}


void PwmDevice::setOnStatus(bool b)
{
    pwmOn_ = b;
}

/*
Need if statements to check and see what message type is in the queue.
Then have functions to handle each different type of message. 
This will make it easier for when we are doing local linking.
*/

/**
 * @brief 
 * 
 */
void genauto::PwmDevice::execute()
{
    if (!inited) {
        ledcSetup(channel, PWM_FREQUENCY, PWM_RESOUTION); // setup PWM 
        ledcAttachPin(pinNumber, channel);
        ledcWrite(channel, 0);
        inited = true;
    }
    Message* Msg = nextMessage();
    if(Msg != NULL)
    {
        if(Msg->type() == EncoderMessage::classMsgType) /// going to need to modify this for directions.
        {
            EncoderMessage* eMsg = (EncoderMessage*)Msg;
            int16_t val = dutyCycle_ + eMsg->value() * increment;
            if(val > 255) dutyCycle_ = 255;
            else if(val <= 0) dutyCycle_ = 0; // change for testing to 0 so no overflow negative.
            else dutyCycle_ = val;
            if(pwmOn_) ledcWrite(channel, dutyCycle_); // only if the pwm device is set to on, write to the pin.
        }
        if(Msg->type() == ButtonMessage::classMsgType)
        {
            ButtonMessage* bMsg = (ButtonMessage*)Msg;
            if(bMsg->pressed() == true) pwmOn_ = !pwmOn_;
            if(pwmOn_) ledcWrite(channel, dutyCycle_);
            else ledcWrite(channel, 0); // turn off the pwm device.
        }
        if(Msg->type() == PwmMessage::classMsgType)
        {
            PwmMessage* pMsg = (PwmMessage*)Msg;
            pwmOn_ = pMsg->onOff();
            int16_t tempDuty = pMsg->dutyCycle();
            if(tempDuty >= -255 && tempDuty <= 255) dutyCycle_ = tempDuty;
            else if(tempDuty > 255) dutyCycle_ = 255;
            else dutyCycle_ = -255;
            if(pwmOn_) ledcWrite(channel, dutyCycle_);
            else ledcWrite(channel, 0);
        }
    }
    ledcWrite(channel, dutyCycle_);
}
