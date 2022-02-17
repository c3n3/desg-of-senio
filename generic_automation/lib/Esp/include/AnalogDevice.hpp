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