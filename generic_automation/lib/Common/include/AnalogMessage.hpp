#ifndef __GENERIC_AUTOMATION_ANALOG_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_ANALOG_MESSAGE_HPP__

#include "Message.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto {
    /**
     * @brief A stepper motor message
     */
    class AnalogMessage : public Message {
        private:
        static constexpr location_t value_location = Message::type_loc + sizeof(msgType_t);
        static constexpr uint16_t msgSize = Message::baseSize + sizeof(uint16_t);
    public:

        /**
         * @brief Construct a new Analog Message object
         * 
         * @param buffer 
         */
        AnalogMessage(uint8_t* buffer, uint16_t bufferSize);
        AnalogMessage();

        /**
         * @brief 
         * 
         * @return uint16_t& 
         */
        uint16_t& value();

        /**
         * @brief Type of the message specific to class
         */
        static constexpr msgType_t classMsgType = 0x0001;
    };
}

#endif
