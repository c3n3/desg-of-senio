#include "../include/StepperDevice.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include "../../Common/include/StepperMotorMessage.hpp"
//#include "../include/Device.hpp"
#include <stdint.h>
#include <AccelStepper.h>

// Class to control stepper
class StepperMotor {
public:
    // Direction enum to clarify direction
    enum Direction {
        Forward = HIGH,
        Backward = LOW
    };
private:
    const uint8_t dirPin_;
    const uint8_t stepPin_;
    const uint16_t stepsPerRev_;
    uint16_t msInterval_;
    Direction direction_;
    unsigned long time_;

    // Simple calculation function
    uint16_t rpmToStepsPerSecond(float rpm)
    {
        float rps = abs(rpm / 60);
        return (rps * stepsPerRev_);
    } 

    uint16_t dpsToStepsPerSecond(float dps)
    {
        const float degreesPerStep = 360 / stepsPerRev_;
        return abs(dps / degreesPerStep);
    } 
public:


    // Construct a stepper motor
    StepperMotor(uint8_t dirPin, uint8_t stepPin, uint16_t stepsPerRev = 200)
        : dirPin_(dirPin), stepPin_(stepPin), stepsPerRev_(stepsPerRev), msInterval_(0), direction_(LOW)
    {
        pinMode(dirPin_, OUTPUT);
        pinMode(stepPin_, OUTPUT);
        digitalWrite(dirPin_, LOW);
        digitalWrite(stepPin_, LOW);
    }


    // In revolutions per minute
    void setSpeedRpm(float rpm)
    {
        if (rpm == 0) {
            msInterval_ = 0;
            return;
        }
        direction_ =  rpm < 0 ? LOW : HIGH;
        // 1000ms / 1s *  (second / step)
        msInterval_ = 1000 / rpmToStepsPerSecond(rpm);
    }

    // In degrees per second
    void setSpeedDps(float dps)
    {
        if (dps == 0) {
            msInterval_ = 0;
            return;
        }
        direction_ = dps < 0 ? LOW : HIGH;
        // 1000ms / 1s *  (second / step)
        msInterval_ = 1000 / dpsToStepsPerSecond(dps);
    }

    // In steps per second
    void setSpeedSps(float sps)
    {
        if (sps == 0) {
            msInterval_ = 0;
            return;
        }
        // 1000ms / 1s *  (second / step)
        msInterval_ = 1000 / sps;
    }

    // In millisecond interval
    void setSpeedMsi(float msi)
    {
        msInterval_ = abs(msi);
        direction_ = msi < 0 ? Backward : Forward;
    }

    // Step the motor
    void step()
    {
        digitalWrite(dirPin_, direction_);
        digitalWrite(stepPin_,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPin_,LOW); 
        delayMicroseconds(500); 
    }

    // Step the motor for a direction
    void step(Direction dir)
    {
        msInterval_ = 0;
        direction_ = dir;
        step();
    }

    // Must be called continuously
    void run()
    {
        if (msInterval_ == 0) return;
        if (millis() - time_ > msInterval_) {
            step();
            time_ += msInterval_;
        }
    }
};

static const uint16_t stepsPerRevolution = 200;

using namespace genauto;

genauto::StepperDevice::StepperDevice(uint8_t stepPin, uint8_t dirPin, minor_t minorId)
    : dirPin(dirPin),
      stepPin(stepPin),
      Subscriber(),
      myStepper(AccelStepper(1, stepPin, dirPin)),
      Device(minorId),
      motorOn(true)
{
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    myStepper.setMaxSpeed(900);
    myStepper.setSpeed(400);
    speed_ = 400;
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
    if (msgs_.dequeue(Msg) == decltype(msgs_)::Success)
    {
        dlog("first if\n");
        if (Msg->type() == EncoderMessage::classMsgType)
        {
            dlog("in encoder if\n");
            EncoderMessage *eMsg = (EncoderMessage *)Msg;
            int16_t val = eMsg->value() * encoderStepScale_; // can be negative, lets it know to move CCW or CW which should be moving the encoder the same.
            myStepper.move(val);
        }
        if (Msg->type() == ButtonMessage::classMsgType)
        {
            ButtonMessage *bMsg = (ButtonMessage *)Msg;
            if (bMsg->pressed() == true)
                motorOn == !motorOn;
        }
        if (Msg->type() == StepperMotorMessage::classMsgType)
        {
            StepperMotorMessage *sMsg = (StepperMotorMessage *)Msg;
            float val = sMsg->value();
            if(sMsg->valueType() == StepperMotorMessage::Speed)
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
        dlog("motor on\n");
        myStepper.run();
    }
}