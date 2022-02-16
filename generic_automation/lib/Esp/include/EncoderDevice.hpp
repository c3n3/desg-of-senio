#ifndef __GENERIC_AUTOMATION_ENCODERDEVICE_HPP__
#define __GENERIC_AUTOMATION_ENCODERDEVICE_HPP__

#include "../../Common/include/Publisher.hpp"
#include <stdint.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class EncoderDevice : public Publisher {
        private:
            uint8_t pinNumber;
            uint8_t pressed_;
    public:

        /**
         * @brief Construct a new Encoder Device object
         * 
         * @param pinNumber 
         */
        EncoderDevice(uint8_t pinNumber);

        /**
         * @brief executes the purpose of the Encoder class
         * 
         */
        void execute();
    };
}

#endif