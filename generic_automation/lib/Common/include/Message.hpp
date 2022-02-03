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
         * @brief used to simply declare message types in an easy way.
         * 
         */
        #define MSG_TYPE(A, B) (((uint16_t)(A)) << 8) | ((uint16_t)(B))

        /**
         * @brief Type of the messag id
         */
        typedef uint16_t msgType_t;

        /**
         * @brief Simple ctor
         *
         * @param id msg id
         */
        Message(const MessageId& id, msgType_t type);

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
        const msgType_t msgType;

        /**
         * @brief Length of the message
         */
        const uint16_t size;

        /**
         * @brief Defines type string for all class
         */
        static const msgType_t classMsgType;
    }; 
}

#endif
