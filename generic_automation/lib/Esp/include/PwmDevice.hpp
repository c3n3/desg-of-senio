#ifndef __GENERIC_AUTOMATION_PWMDEVICE_HPP__
#define __GENERIC_AUTOMATION_PWMDEVICE_HPP__

#include "../../Common/include/Subscriber.hpp"
#include "../../Common/include/Device.hpp"
#include <stdint.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class PwmDevice : public Subscriber, public Device {
    public:
        struct Pwmdir {
            uint8_t p1;
            uint8_t p2;
        };
    private:
        uint8_t pinNumber;
        uint8_t channel;
        int16_t dutyCycle_ = 0; // can be negative for backwards direction for motor.
        bool pwmOn_ = true;
        uint16_t increment = 5;
        Pwmdir dir_;
        bool inited;
    public:

        /**
         * @brief Output the current state of the pwm
         */
        void output();

        /**
         * @brief Set direction
         */
        void dir(bool dir);

        /**
         * @brief Construct a new Pwm Device object
         * 
         * @param pinNumber 
         */
        PwmDevice(Pwmdir dirPins, uint8_t pinNumber, uint8_t channel, minor_t minorId);

        /**
         * @brief Get the Duty Cycle object
         * 
         * @return uint8_t 
         */
        int16_t getDutyCycle();


        /**
         * @brief Set the Duty Cycle object
         * 
         * @param dutyCycle 
         */
        void setDutyCycle(int16_t dutyCycle);


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

        /**
         * @brief Gets the sub*
         *
         * @return Subscriber*
         */
        Subscriber* sub();
    };
}

#endif
