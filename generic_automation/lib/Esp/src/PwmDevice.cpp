#include "../include/PwmDevice.hpp"
#include <stdint.h>

static const uint16_t PWM_FREQUENCY = 5000;
static const uint8_t PWM_RESOUTION = 8;
const genauto::Message::msgType_t genauto::Message::classMsgType = MSG_TYPE('A', 'C');

/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 * 
 * @param pinNumber 
 */
genauto::PwmDevice::PwmDevice(uint8_t pinNumber, uint8_t channel)  
    : pinNumber(pinNumber),
    channel(channel),
    Subscriber(10)
{
    ledcSetup(channel, PWM_FREQUENCY, PWM_RESOUTION); // setup PWM 
    ledcAttachPin(pinNumber, channel);
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t genauto::PwmDevice::getDutyCycle()
{
    return dutyCycle_;
}


/**
 * @brief 
 * 
 * @param dutyCycle 
 */
void genauto::PwmDevice::setDutyCycle(uint8_t dutyCycle)
{
    dutyCycle_ = dutyCycle;
}

/**
 * @brief 
 * 
 * @param timeOn 
 */
void genauto::PwmDevice::setTimeOn(uint32_t timeOn)
{
    timeOn_ = timeOn;
    startTime_ = millis();
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
    Message* Msg = NULL;
    if(msgs_.dequeue(Msg) == Queue<Message*>::Success)
    {
        if(Msg->msgType == EncoderMessage::classMsgType)
        {
            EncoderMessage* eMsg = (EncoderMessage*)Msg;
            uinit6_t curDuty = dutyCycle_;
            
        }
        if(Msg->msgType == ButtonMessage::classMsgType)
        {
            ButtonMessage* bMsg = (ButtonMessage*)Msg;
            if(pwmOn_ == bMsg.onStatus) pwmOn_ = !pwmOn_;
        }
        if(Msg->msgType == TimeOnMessage::classMsgType)
        {
            TimeOnMessage* tMsg = (TimeOnMessage*)Msg;
            setTimeOn(TimeOnMessage.time);
        }
    }

    if((millis() - startTime_) < timeOn_)
    {
        if(!pwmOn_) ledcWrite(channel, dutyCycle);
    }
    else{
        if(pwmOn_) pwmOn = false;
        ledcWrite(channel, 0);
    }
}
