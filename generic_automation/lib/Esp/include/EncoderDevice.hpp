#ifndef __GENERIC_AUTOMATION_ENCODERDEVICE_HPP__
#define __GENERIC_AUTOMATION_ENCODERDEVICE_HPP__

#include "../../Common/include/Publisher.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include "../../Common/include/Device.hpp"
#include <stdint.h>
#include <ESP32Encoder.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class EncoderDevice : public Publisher, public Device {
        private:
            uint8_t pinA;
            uint8_t pinB;
            bool flag;
            int16_t count = 0;
            int16_t c;
            unsigned long lastTime = 0;
            ESP32Encoder encoder;
            EncoderMessage eMsg;
            bool inited;
    public:

        /**
         * @brief Construct a new Encoder Device object
         * 
         * @param pinNumber 
         */
        EncoderDevice(uint8_t pinA, uint8_t pinB, minor_t minorId);

        /**
         * @brief executes the purpose of the Encoder class
         * 
         */
        void execute();
        
        /**
         * @brief 
         * 
         * @return Message* 
         */
        Message *tryGet();

        Publisher* pub();
    };
}

#endif