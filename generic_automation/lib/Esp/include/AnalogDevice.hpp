#ifndef __GENERIC_AUTOMATION_AnalogDEVICE_HPP__
#define __GENERIC_AUTOMATION_AnalogDEVICE_HPP__

#include "../../Common/include/Publisher.hpp"
#include <stdint.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class AnalogDevice : public Publisher {
        private:
            uint8_t pinNumber;
            uint16_t value;
            bool flag;
            unsigned long lastTime = 0;
            unsigned long readTime = 0;
            int16_t accumValue = 0  // sum of the values read in during ~ 250ms interval.
            uint8_t count = 0; // number of values summed into accumValue
    public:

        /**
         * @brief Construct a new Analog Device object
         * 
         * @param pinNumber 
         */
        AnalogDevice(uint8_t pinNumber);

        /**
         * @brief executes the purpose of the Analog class
         * 
         */
        void execute();
    };
}

#endif