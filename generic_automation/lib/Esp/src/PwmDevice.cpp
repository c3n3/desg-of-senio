#include "../include/PwmDevice.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include "../../Common/include/PwmMessage.hpp"
#include <stdint.h>

static const uint16_t PWM_FREQUENCY = 5000;
static const uint8_t PWM_RESOUTION = 8;
//const genauto::Message::msgType_t genauto::Message::classMsgType = MSG_TYPE('A', 'C');

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
    dlog("Here\n");
    if (!inited) {
    dlog("Here\n");
        ledcSetup(channel, PWM_FREQUENCY, PWM_RESOUTION); // setup PWM 
    dlog("Here\n");
        ledcAttachPin(pinNumber, channel);
    dlog("Here\n");
        ledcWrite(channel, 0);
    dlog("Here\n");
        inited = true;
    dlog("Here\n");
    }
    dlog("Here\n");
    Message* Msg = NULL;
    if(msgs_.dequeue(Msg) == decltype(msgs_)::Success)
    {
    dlog("Here\n");
        if(Msg->type() == EncoderMessage::classMsgType)
        {
    dlog("Here\n");
            EncoderMessage* eMsg = (EncoderMessage*)Msg;
            int16_t val = dutyCycle_ + eMsg->value() * increment;
            if(val > 255) dutyCycle_ = 255;
            else if(val < -255) dutyCycle_ = 0;
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
