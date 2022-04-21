#ifndef __GENERIC_AUTOMATION_STEPPERMOTOR_HPP__
#define __GENERIC_AUTOMATION_STEPPERMOTOR_HPP__

#include <stdint.h>
#include "Arduino.h"
#include "../../Common/include/Log.hpp"
namespace genauto
{
    // Class to control stepper
    class StepperMotor
    {
    public:
        // Direction enum to clarify direction
        enum Direction
        {
            Forward = HIGH,
            Backward = LOW
        };

    private:
        const uint8_t dirPin_;
        const uint8_t stepPin_;
        const uint16_t stepsPerRev_;
        uint16_t msInterval_;
        uint16_t toStep_;
        float prevDps_;
        bool coutingSteps_;
        Direction direction_;
        unsigned long time_;

        float dpsToStepsPerSecond(float dps);

    public:
        // Construct a stepper motor
        StepperMotor(uint8_t dirPin, uint8_t stepPin, uint16_t stepsPerRev = 200);

        // In degrees per second
        void setSpeedDps(float dps);

        // In steps per second
        void setSpeedSps(float sps);

        void stop();

        void move(float dps, float degrees);

        // Step the motor
        void step();

        // Step the motor for a direction
        void step(Direction dir);

        bool isMoving();

        // Must be called continuously
        void tick();
    };
}
#endif
