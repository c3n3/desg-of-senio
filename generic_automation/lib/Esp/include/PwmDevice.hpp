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
            int16_t dutyCycle_; // can be negative for backwards direction for motor.
            bool pwmOn_;
            uint16_t increment;
    public:

        /**
         * @brief Construct a new Pwm Device object
         * 
         * @param pinNumber 
         */
        PwmDevice(uint8_t pinNumber, uint8_t channel);


        /**
         * @brief Get the Duty Cycle object
         * 
         * @return uint8_t 
         */
        uint8_t getDutyCycle();


        /**
         * @brief Set the Duty Cycle object
         * 
         * @param dutyCycle 
         */
        void setDutyCycle(uint8_t dutyCycle);


        /**
         * @brief Get the On Status object
         * 
         * @return true 
         * @return false 
         */
        bool getOnStatus();

        /**
         * @brief Set the On Status object
         * 
         * @param onStatus 
         */
        void setOnStatus(bool onStatus);


        /**
         * @brief executes the purpose of the PWM class
         * 
         */
        void execute();

    };
}

#endif
