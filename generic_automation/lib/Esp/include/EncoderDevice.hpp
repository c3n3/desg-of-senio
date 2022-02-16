#ifndef __GENERIC_AUTOMATION_ENCODERDEVICE_HPP__
#define __GENERIC_AUTOMATION_ENCODERDEVICE_HPP__

#include "../../Common/include/Publisher.hpp"
#include <stdint.h>
#include <ESP32Encoder.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class EncoderDevice : public Publisher {
        private:
            uint8_t pinA;
            uint8_t pinB;
            bool flag;
            int16_t count;
    public:

        /**
         * @brief Construct a new Encoder Device object
         * 
         * @param pinNumber 
         */
        EncoderDevice(uint8_t pinA, uint8_t pinB);

        /**
         * @brief executes the purpose of the Encoder class
         * 
         */
        void execute();
    };
}

#endif