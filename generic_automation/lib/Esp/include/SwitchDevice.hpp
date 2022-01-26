#ifndef __GENERIC_AUTOMATION_SWITCHDEVICE_HPP__
#define __GENERIC_AUTOMATION_SWITCHDEVICE_HPP__

#include <stdint.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class SwitchDevice {
    public:

        /**
         * @brief Construct a new Switch Device object
         * 
         * @param pinNumber 
         */
        SwitchDevice(uint8_t pinNumber);

        /**
         * @brief Set the High Low object
         * 
         * @param state 
         */
        void setHighLow(bool state);

    };
}

#endif
