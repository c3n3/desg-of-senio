#include "../include/StepperDevice.hpp"
//#include "../include/Device.hpp"
#include <stdint.h>
#include <AccelStepper.h>

static const uint16_t stepsPerRevolution = 200;

using namespace genauto;

genauto::StepperDevice::StepperDevice(uint8_t stepPin, uint8_t dirPin, uint8_t minorId)
    : dirPin(dirPin),
      stepPin(stepPin),
      Subscriber(10),
      minorId(MinorId),
      mystepper(AccelStepper::DRIVER(1, stepPin, dirPin))
{
    myStepper.connectToPins(stepPin, dirPin);
}

/**
 * @brief Set the Enc Step Scale object
 *
 * @param encStepScale
 */
void StepperDevice::setEncStepScale(uint8_t encStepScale)
{
    encoderStepScale_ = encStepScale;
}

/**
 * @brief Get the Enc Step Scale object, the scale for how many steps are taken for each click of an encoder.
 *
 * @return uint8_t
 */
uint8_t StepperDevice::getEncStepScale()
{
    return encoderStepScale_;
}

/**
 * @brief Set the Speed object
 *
 * @param speed
 */
void StepperDevice::setSpeed(float speed)
{
    speed_ = speed;
    myStepper.setSpeed(speed_); // negative speed for CCW, positive speed for CW
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

/**
 * @brief
 *
 * @return float
 */
float StepperDevice::getAngle()
{
    return angle_;
}

/**
 * @brief
 *
 */
void genauto::StepperDevice::execute()
{
    Message *Msg = NULL;
    if (msgs_.dequeue(Msg) == Queue<Message *>::Success)
    {
        if (Msg->type == EncoderMessage::classMsgType)
        {
            EncoderMessage *eMsg = (EncoderMessage *)Msg;
            long val = eMsg->value() * encoderStepScale_; // can be negative, lets it know to move CCW or CW which should be moving the encoder the same.
            myStepper.moveTo(val);
        }
        if (Msg->type == ButtonMessage::classMsgType)
        {
            ButtonMessage *bMsg = (ButtonMessage *)Msg;
            if (bMsg->pressed() == true)
                motorOn == !motorOn;
        }
        if (Msg->type == StepperMotorMessage::classMsgType)
        {
            StepperMotorMessage *sMsg = (StepperMotorMessage *)Msg;
            float val = sMsg->value();
            if(sMsg->ValueType() == StepperMotorMessage::Speed)
            {
                setSpeed(val);
            }
            else
            {
                int32_t stepsToTake = (int32_t)(val/360); // this needs to be in negative degrees to move CCW. 
                                                          // all relative, starting position is current position
                myStepper.moveTo(stepsToTake); 
            }
        }
    }
    if (motorOn)
    {
        myStepper.run();
    }
}