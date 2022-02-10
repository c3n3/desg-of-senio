#include "../include/StepperDevice.hpp"
//#include "../include/Device.hpp"
#include <stdint.h>
#include <Stepper.h>

static const uint16_t stepsPerRevolution = 200;


using namespace genauto;

genauto::StepperDevice::StepperDevice(uint8_t stepPin, uint8_t dirPin, uint8_t minorId)
    : dirPin(dirPin),
      stepPin(stepPin),
      Subscriber(10),
      minorId(MinorId)
{
    myStepper.connectToPins(stepPin, dirPin);
}

/**
 * @brief Set the Speed object
 *
 * @param speed
 */
void StepperDevice::setSpeed(float speed)
{
    speed_ = speed;
}

/**
 * @brief Get the Speed object
 * 
 * @return float 
 */
float StepperDevice::getSpeed()
{
    return speed_;
}

/**
 * @brief Set the Direction object
 *
 * @param dir
 */
void StepperDevice::setDirection(uint8_t dir)
{
    direction_ = dir;
}

/**
 * @brief Get the Direction object
 * 
 * @return uint8_t 
 */
uint8_t StepperDevice::getDirection()
{
    return direction_;
}

/**
 * @brief Set the Angle object
 *
 * @param angle
 */
void StepperDevice::setAngle(float angle)
{
    angle_ = angle;
}


float StepperDevice::getAngle()
{
    return angle_;
}

void genauto::StepperDevice::execute()
{
    Message* Msg = NULL;
    if(msgs_.dequeue(Msg) == Queue<Message*>::Success)
    {
        if(Msg->type == EncoderMessage::classMsgType)
        {
            EncoderMessage* eMsg = (EncoderMessage*)Msg;
            int val = eMsg->value() * encoderStepScale_;
            myStepper.setTargetPositionRelativeInSteps(val);
        }
        if(Msg->type == ButtonMessage::classMsgType)
        {
            ButtonMessage* bMsg = (ButtonMessage*)Msg;
            if(bMsg->pressed() == true) 
        }
    }
}