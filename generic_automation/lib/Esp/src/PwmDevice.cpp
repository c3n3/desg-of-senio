#include "../include/PwmDevice.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include "../../Common/include/SimpleMessages.hpp"
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
genauto::PwmDevice::PwmDevice(Pwmdir dir, uint8_t pinNumber, uint8_t channel, minor_t minorId)
    : pinNumber(pinNumber),
    channel(channel),
    Subscriber(),
    Device(minorId),
    inited(false),
    dir_(dir)
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

static void limit(int16_t& val, int16_t low, int16_t up)
{
    if (val > up) {
        val = up;
    } else if (val < low) {
        val = low;
    }
}

void genauto::PwmDevice::execute()
{
    if (!inited) {
        pinMode(dir_.p1, OUTPUT);
        pinMode(dir_.p2, OUTPUT);
        ledcSetup(channel, PWM_FREQUENCY, PWM_RESOUTION); // setup PWM 
        ledcAttachPin(pinNumber, channel);
        ledcWrite(channel, 0);
        inited = true;
    }
    Message* Msg = nextMessage();
    if(Msg != NULL)
    {
        if(Msg->type() == EncoderMessage::classMsgType)
        {
            EncoderMessage* eMsg = (EncoderMessage*)Msg;
            int16_t val = dutyCycle_ + eMsg->value() * increment;

            // Limit
            limit(val, -255, 255);
            dutyCycle_ += val;
            limit(dutyCycle_, -255, 255);
        }
        else if(Msg->type() == ButtonMessage::classMsgType)
        {
            pwmOn_ = !pwmOn_;
        }
        else if(Msg->type() == PwmMessage::classMsgType)
        {
            PwmMessage* pMsg = (PwmMessage*)Msg;
            pwmOn_ = pMsg->onOff();
            dutyCycle_ = pMsg->dutyCycle();
            limit(dutyCycle_, -255, 255);
        }
        else if (Msg->type() == FlipMessage::classMsgType) {
            FlipMessage sMsg = FlipMessage(Msg->getBuffer(), Msg->size());
            pwmOn_ = sMsg.on();
        }
        else if (Msg->type() == IncrementMessage::classMsgType) {
            IncrementMessage sMsg = IncrementMessage(Msg->getBuffer(), Msg->size());
            increment = sMsg.increment();
        }
    }
    output();
}


Subscriber* genauto::PwmDevice::sub()
{
    return static_cast<Subscriber*>(this);
}


void genauto::PwmDevice::dir(bool dir)
{
    digitalWrite(dir_.p1, dir);
    digitalWrite(dir_.p2, !dir);
}

void genauto::PwmDevice::output()
{
    dir(dutyCycle_ < 0);
    ledcWrite(channel, abs(dutyCycle_) * pwmOn_);
}
