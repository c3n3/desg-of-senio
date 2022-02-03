#ifndef __GENERIC_AUTOMATION_STEPPERDEVICE_HPP__
#define __GENERIC_AUTOMATION_STEPPERDEVICE_HPP__

#include <stdint.h>
#include <Stepper.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class StepperDevice {
    private:
    uint8_t stepPin;
    uint8_t dirPin;
    Stepper myStepper;
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
        void setSpeed(uint8_t speed);

        /**
         * @brief Set the Direction object
         * 
         * @param dir 
         */
        void setDirection(uint8_t dir);

        /**
         * @brief Set the Angle object
         * 
         * @param angle 
         */
        void setAngle(uint8_t angle);

    };
}

#endif
