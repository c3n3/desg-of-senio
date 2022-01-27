#ifndef __GENERIC_AUTOMATION_PWMDEVICE_HPP__
#define __GENERIC_AUTOMATION_PWMDEVICE_HPP__

#include "../../Common/include/Subscriber.hpp"
#include <stdint.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class PwmDevice : public Subscriber {
        private:
            uint8_t pinNumber;
            uint8_t channel;
            uint8_t dutyCycle_;
            uint32_t timeOn_;
            uint8_t dir_;
            uint32_t startTime_;
            bool pwmOn_;
    public:

        /**
         * @brief Construct a new Pwm Device object
         * 
         * @param pinNumber 
         */
        PwmDevice(uint8_t pinNumber, uint8_t channel);


        /**
         * @brief Set the Duty Cycle object
         * 
         * @param dutyCycle 
         */
        void setDutyCycle(uint8_t dutyCycle);


        /**
         * @brief Set the Time On object
         * 
         * @param timeOn 
         */
        void setTimeOn(uint32_t timeOn);


        /**
         * @brief Set the Direction object
         * 
         * @param dir 
         */
        void setDirection(uint8_t dir);

        /**
         * @brief executes the purpose of the PWM class
         * 
         */
        void execute();

    };
}

#endif
