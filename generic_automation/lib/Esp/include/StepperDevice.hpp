#ifndef __GENERIC_AUTOMATION_STEPPERDEVICE_HPP__
#define __GENERIC_AUTOMATION_STEPPERDEVICE_HPP__

#include <stdint.h>
#include <ESP_FlexyStepper.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class StepperDevice {
    private:
    float speed_;
    float angle_;
    uint8_t encoderStepScale_ = 10;
    //float encoderAngleIncrement_;
    uint8_t direction_;
    uint8_t stepPin_;
    uint8_t dirPin_;
    ESP_FlexyStepper myStepper;
    public:

        /**
         * @brief Construct a new Stepper Device object
         * 
         * @param pinNumber 
         */
        StepperDevice(uint8_t stepPin, uint8_t dirPin);

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

    };
}

#endif
