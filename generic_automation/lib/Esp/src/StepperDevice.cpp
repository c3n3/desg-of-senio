#include "../include/StepperDevice.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include "../../Common/include/StepperMotorMessage.hpp"
#include "../../Common/include/SimpleMessages.hpp"
#include "../../Common/include/Timer.hpp"
//#include "../include/Device.hpp"
#include <stdint.h>
#include <AccelStepper.h>
#include "../include/StepperMotor.hpp"

static const uint16_t stepsPerRevolution = 200;

using namespace genauto;

// // Construct a stepper motor
// StepperMotor::StepperMotor(uint8_t dirPin, uint8_t stepPin, uint16_t stepsPerRev = 200)
//     : dirPin_(dirPin), stepPin_(stepPin), stepsPerRev_(stepsPerRev), msInterval_(0), direction_((Direction)LOW)
// {
//     pinMode(dirPin_, OUTPUT);
//     pinMode(stepPin_, OUTPUT);
//     digitalWrite(dirPin_, LOW);
//     digitalWrite(stepPin_, LOW);
// }


// // In revolutions per minute
// void StepperMotor::setSpeedRpm(float rpm)
// {
//     if (rpm == 0) {
//         msInterval_ = 0;
//         return;
//     }
//     direction_ =  (Direction)(rpm < 0 ? LOW : HIGH);
//     // 1000ms / 1s *  (second / step)
//     msInterval_ = 1000 / rpmToStepsPerSecond(rpm);
// }

// // In degrees per second
// void StepperMotor::setSpeedDps(float dps)
// {
//     if (dps == 0) {
//         msInterval_ = 0;
//         return;
//     }
//     direction_ = (Direction)(dps < 0 ? LOW : HIGH);
//     // 1000ms / 1s *  (second / step)
//     msInterval_ = 1000 / dpsToStepsPerSecond(dps);
// }

// // In steps per second
// void StepperMotor::setSpeedSps(float sps)
// {
//     if (sps == 0) {
//         msInterval_ = 0;
//         return;
//     }
//     // 1000ms / 1s *  (second / step)
//     msInterval_ = 1000 / sps;
// }

// // In millisecond interval
// void StepperMotor::setSpeedMsi(float msi)
// {
//     msInterval_ = abs(msi);
//     direction_ = (Direction)(msi < 0 ? Backward : Forward);
// }

// // Step the motor
// void StepperMotor::step()
// {
//     digitalWrite(dirPin_, direction_);
//     digitalWrite(stepPin_,HIGH); 
//     delayMicroseconds(500); 
//     digitalWrite(stepPin_,LOW); 
//     delayMicroseconds(500); 
// }

// // Step the motor for a direction
// void StepperMotor::step(Direction dir)
// {
//     msInterval_ = 0;
//     direction_ = dir;
//     step();
// }

// // Must be called continuously
// void StepperMotor::run()
// {
//     if (msInterval_ == 0) return;
//     if (millis() - time_ > msInterval_) {
//         step();
//         time_ += msInterval_;
//     }
// }


genauto::StepperDevice::StepperDevice(uint8_t stepPin, uint8_t dirPin, minor_t minorId)
    : dirPin(dirPin),
      stepPin(stepPin),
      Subscriber(),
      myStepper(dirPin, stepPin),
      Device(minorId),
      motorOn(true),
      mode(Degrees),
      force_(false)
{
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    // myStepper.setMaxSpeed(900);
    // myStepper.setSpeed(400);
    // speed_ = 400;
    // myStepper.setSpeedDps(speed_);
}

/**
 * @brief Set the Enc Step Scale object
 *
 * @param encStepScale
 */
void StepperDevice::setEncStepScale(float encStepScale)
{
    encoderStepScale_ = encStepScale;
}

/**
 * @brief Get the Enc Step Scale object, the scale for how many steps are taken for each click of an encoder.
 *
 * @return uint8_t
 */
float StepperDevice::getEncStepScale()
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
    myStepper.setSpeedDps(speed_);
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
    //Timer t("NAME");
    Message *Msg = nextMessage();
    if (Msg != NULL)
    {
        dlog("Running stepper\n");
        if (Msg->type() == EncoderMessage::classMsgType && !force_)
        {
            // dlog("in encoder if\n");
            EncoderMessage *eMsg = (EncoderMessage *)Msg;
            int16_t val = (int16_t)eMsg->value() * encoderStepScale_;
            mode = Degrees;
            motorOn = true;
            force_ = false;
            myStepper.move(speed_, val);
        }
        else if (Msg->type() == ButtonMessage::classMsgType && !force_)
        {
            motorOn = false;
            myStepper.stop();
        }
        else if (Msg->type() == StepperMotorMessage::classMsgType)
        {
            StepperMotorMessage *sMsg = (StepperMotorMessage *)Msg;
            float val = sMsg->value();
            encoderStepScale_ = sMsg->stepScale() > 0 ? sMsg->stepScale() : encoderStepScale_;
            
            if (sMsg->modeType() == StepperMotorMessage::DegreesSecond)
            {
                mode = DegreesSecond;
                force_ = false;
                setSpeed(val);
            }
            else if (sMsg->modeType() == StepperMotorMessage::Degrees)
            {
                mode = Degrees;
                // dlog("val: %d\n", (int)val);
                // dlog("speed: %d\n", (int)speed_);
                force_ = sMsg->force();
                if (force_) {
                    dlog("Forcing motor\n");
                }
                myStepper.move(speed_, val);
            }
            motorOn = true;
        }
        else if (Msg->type() == FlipMessage::classMsgType)
        {
            FlipMessage *sMsg = (FlipMessage *)Msg;
            motorOn = sMsg->on();
        }
        else if (Msg->type() == IncrementMessage::classMsgType) {
            IncrementMessage sMsg = IncrementMessage(Msg->getBuffer(), Msg->size());
            encoderStepScale_ = sMsg.increment();
        }
    }
    if (motorOn)
    {
        myStepper.tick();
    }
    if (force_ && !myStepper.isMoving()) {
        force_ = false;
    }
}

Subscriber* genauto::StepperDevice::sub()
{
    return static_cast<Subscriber*>(this);
}
