#ifndef __GENERIC_AUTOMATION_STEPPERDEVICE_HPP__
#define __GENERIC_AUTOMATION_STEPPERDEVICE_HPP__

#include <stdint.h>
#include <AccelStepper.h>
#include "../../Common/include/Subscriber.hpp"
#include "../../Common/include/Device.hpp"
#include "StepperMotor.hpp"

namespace genauto {
    /**
     * @brief Abstract message
     */
    class StepperDevice : public Subscriber, public Device {
    private:
    float speed_ = 180;
    float angle_;
    float encoderStepScale_ = 1;
    //float encoderAngleIncrement_;
    uint8_t direction_;
    uint8_t stepPin;
    uint8_t dirPin;
    bool motorOn;
    StepperMotor myStepper;

    enum Mode
        {
            Degrees,
            DegreesSecond
        }mode;
    public:

        /**
         * @brief Construct a new Stepper Device object
         * 
         * @param pinNumber 
         */
        StepperDevice(uint8_t stepPin, uint8_t dirPin, minor_t minorId);

        /**
         * @brief Set the Enc Step Scale object
         * 
         * @param encStepScale 
         */
        void setEncStepScale(float encStepScale);

        /**
         * @brief Get the Enc Step Scale object, the scale for how many steps are taken for each click of an encoder.
         * 
         * @return uint8_t 
         */
        float getEncStepScale();

        /**
         * @brief Set the Speed object
         * 
         * @param speed 
         */
        void setSpeed(float speed);

        /**
         * @brief Get the Speed object
         * 
         * @return uint8_t 
         */
        float getSpeed();

        /**
         * @brief Set the Direction object
         * 
         * @param dir 
         */
        void setDirection(uint8_t dir);

        /**
         * @brief Get the Direction object
         * 
         * @return uint8_t 
         */
        uint8_t getDirection();

        /**
         * @brief Set the Angle object
         * 
         * @param angle 
         */
        void setAngle(float angle);

        /**
         * @brief Get the Angle object
         * 
         * @return uint8_t 
         */
        float getAngle();

        /**
         * @brief 
         * 
         */
        void execute();

        Subscriber* sub();
    };
}

#endif
