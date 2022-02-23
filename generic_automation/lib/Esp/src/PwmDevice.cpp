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
    dlog("\n");
    if (!inited) {
    dlog("\n");
        // ledcSetup(channel, PWM_FREQUENCY, PWM_RESOUTION); // setup PWM 
    dlog("\n");
        // ledcAttachPin(pinNumber, channel);
    dlog("\n");
    dlog("\n");
        inited = true;
    dlog("\n");
    }
    dlog("\n");
    Message* Msg = NULL;
    dlog("\n");
    if(msgs_.dequeue(Msg) == decltype(msgs_)::Success)
    dlog("\n");
    {
    dlog("\n");
        if(Msg->type() == EncoderMessage::classMsgType)
        {
    dlog("\n");
            EncoderMessage* eMsg = (EncoderMessage*)Msg;
    dlog("\n");
            int16_t val = dutyCycle_ + eMsg->value() * increment;
    dlog("\n");
            if(val > 255) dutyCycle_ = 255;
            else if(val < -255) dutyCycle_ = 0;
            else dutyCycle_ = val;
            if(pwmOn_) ledcWrite(channel, dutyCycle_); // only if the pwm device is set to on, write to the pin.
    dlog("\n");
        }
    dlog("\n");
        if(Msg->type() == ButtonMessage::classMsgType)
        {
    dlog("\n");
            ButtonMessage* bMsg = (ButtonMessage*)Msg;
            if(bMsg->pressed() == true) pwmOn_ = !pwmOn_;
            if(pwmOn_) ledcWrite(channel, dutyCycle_);
            else ledcWrite(channel, 0); // turn off the pwm device.
    dlog("\n");
        }
        if(Msg->type() == PwmMessage::classMsgType)
        {
    dlog("\n");
            PwmMessage* pMsg = (PwmMessage*)Msg;
            pwmOn_ = pMsg->onOff();
            int16_t tempDuty = pMsg->dutyCycle();
            if(tempDuty >= -255 && tempDuty <= 255) dutyCycle_ = tempDuty;
            else if(tempDuty > 255) dutyCycle_ = 255;
            else dutyCycle_ = -255;
            if(pwmOn_) ledcWrite(channel, dutyCycle_);
            else ledcWrite(channel, 0);
    dlog("\n");
        }
    }
    ledcWrite(channel, dutyCycle_);
    dlog("\n");
}
