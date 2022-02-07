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
    class EncoderMessage : public Message16_t {
    private:
    static const uint16_t value_location = type_location + sizeof(uint16_t);
    public:

        /**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
        EncoderMessage(MessageId id, uint16_t val);

        /**
         * @brief gets the value of the message
         *
         * @return uint16_t
         */
        uint16_t getValue();

        /**
         * @brief Set the Value object
         * 
         * @param value 
         */
        void setValue(uint16_t value);


        /**
         * @brief Convert to string
         *
         * @param sb
         */
        void toString(StringBuilder& sb);
        
        /**
         * @brief Type of the message specific to class
         */
        static const Message::msgType_t classMsgType;
    private:
        uint16_t value_;
    };
}

#endif
