#include "../include/StepperMotor.hpp"

using namespace genauto;

// Construct a stepper motor
StepperMotor::StepperMotor(uint8_t dirPin, uint8_t stepPin, uint16_t stepsPerRev)
    : dirPin_(dirPin), stepPin_(stepPin), stepsPerRev_(stepsPerRev), msInterval_(0), direction_(Forward), toStep_(0), coutingSteps_(false)
{
    pinMode(dirPin_, OUTPUT);
    pinMode(stepPin_, OUTPUT);
    digitalWrite(dirPin_, LOW);
    digitalWrite(stepPin_, LOW);
}

float StepperMotor::dpsToStepsPerSecond(float dps)
{
    const float degreesPerStep = 360.0 / (float)stepsPerRev_;
    return abs(dps) / degreesPerStep;
}

// In degrees per second
void StepperMotor::setSpeedDps(float dps)
{
    coutingSteps_ = false;
    if (dps == 0) {
        prevDps_ = 0;
        msInterval_ = 0;
        return;
    }
    if (dps == prevDps_) {
        return;
    }
    direction_ = dps < 0 ? Backward : Forward;
    // 1000ms / 1s *  (second / step)
    msInterval_ = 1000.0 / dpsToStepsPerSecond(dps);
    time_ = millis();
    prevDps_ = dps;
}

// In steps per second
void StepperMotor::setSpeedSps(float sps)
{
    coutingSteps_ = false;
    if (sps == 0) {
        msInterval_ = 0;
        return;
    }
    direction_ = sps < 0 ? Backward : Forward;

    // 1000ms / 1s *  (second / step)
    msInterval_ = 1000 / sps;
    time_ = millis();
}

void StepperMotor::stop()
{
    msInterval_ = 0;
    coutingSteps_ = false;
    prevDps_ = 0;
    toStep_ = 0;
}

void StepperMotor::move(float dps, float degrees)
{
    const float stepsPerDegree = stepsPerRev_ / 360.0;
    const float sign = degrees < 0 ? -1 : 1;
    setSpeedDps(sign*dps);
    toStep_ = sign * degrees * stepsPerDegree;
    coutingSteps_ = true;
}

// Step the motor
void StepperMotor::step()
{
    digitalWrite(dirPin_, direction_);
    digitalWrite(stepPin_,HIGH); 
    delayMicroseconds(100); 
    digitalWrite(stepPin_,LOW); 
    delayMicroseconds(100); 
}

// Step the motor for a direction
void StepperMotor::step(Direction dir)
{
    msInterval_ = 0;
    direction_ = dir;
    step();
}

bool StepperMotor::isMoving()
{
    return msInterval_ != 0;
}

// Must be called continuously
void StepperMotor::tick()
{
    if (msInterval_ == 0) return;
    if (millis() - time_ > msInterval_) {
        step();
        if (toStep_-- == 0) {
            stop();
        }
        time_ += msInterval_;
    }
}