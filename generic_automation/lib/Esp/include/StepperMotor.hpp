#ifndef __GENERIC_AUTOMATION_STEPPERMOTOR_HPP__
#define __GENERIC_AUTOMATION_STEPPERMOTOR_HPP__

#include <stdint.h>

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
            : dirPin_(dirPin), stepPin_(stepPin), stepsPerRev_(stepsPerRev), msInterval_(0), direction_(Forward)
        {
            pinMode(dirPin_, OUTPUT);
            pinMode(stepPin_, OUTPUT);
            digitalWrite(dirPin_, LOW);
            digitalWrite(stepPin_, LOW);
        }

        // In revolutions per minute
        void setSpeedRpm(float rpm)
        {
            if (rpm == 0)
            {
                msInterval_ = 0;
                return;
            }
            direction_ = (Direction)(rpm < 0 ? LOW : HIGH);
            // 1000ms / 1s *  (second / step)
            msInterval_ = 1000 / rpmToStepsPerSecond(rpm);
        }

        // In degrees per second
        void setSpeedDps(float dps)
        {
            if (dps == 0)
            {
                msInterval_ = 0;
                return;
            }
            direction_ = (Direction)(dps < 0 ? LOW : HIGH);
            // 1000ms / 1s *  (second / step)
            if(dps > -500 && dps < 500) msInterval_ = 1000 / dpsToStepsPerSecond(dps);
        }

        // In steps per second
        void setSpeedSps(float sps)
        {
            if (sps == 0)
            {
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
            digitalWrite(stepPin_, HIGH);
            //delayMicroseconds(500);
            digitalWrite(stepPin_, LOW);
            //delayMicroseconds(500);
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
            if (msInterval_ == 0)
                return;
            if (millis() - time_ > msInterval_)
            {
                step();
                time_ += msInterval_;
            }
        }
    };
}
#endif