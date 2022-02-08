#ifndef __GENERIC_AUTOMATION_ENCODER_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_ENCODER_MESSAGE_HPP__

#include "Message.hpp"
#include "StringBuilder.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto {
    /**
     * @brief A stepper motor message
     */
    class EncoderMessage : public Message {
        private:
        static const uint16_t value_location = Message::type_loc + sizeof(msgType_t);
        static constexpr uint16_t msgSize = Message::baseSize + sizeof(uint16_t);
    public:

        /**
         * @brief Construct a new Encoder Message object
         * 
         * @param buffer 
         */
        EncoderMessage(uint8_t* buffer = nullptr);

        /**
         * @brief 
         * 
         * @return uint16_t& 
         */
        uint16_t& value();

        /**
         * @brief Convert to string
         *
         * @param sb
         */
        void toString(StringBuilder& sb);
        
        /**
         * @brief Type of the message specific to class
         */
        static const msgType_t classMsgType;
    };
}

#endif
