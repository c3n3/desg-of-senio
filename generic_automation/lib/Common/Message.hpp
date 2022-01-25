#ifndef __GENERIC_AUTOMATION_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_MESSAGE_HPP__

#include "StringBuilder.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class Message {
    public:
        /**
         * @brief Type of the messag id
         */
        typedef uint8_t msgType_t[2];

        /**
         * @brief Simple ctor
         *
         * @param id msg id
         */
        Message(const MessageId& id);

        /**
         * @brief Message id
         */
        const MessageId id;

        /**
         * @brief Simple to string function written such that no
         * standard library is needed
         *
         * @param buf buffer to store the new string
         * @param size the size of the input buffer
         */
        virtual void toString(StringBuilder& sb);

        /**
         * @brief Type of the message
         */
        static const msgType_t msgType;
    };
}

#endif
