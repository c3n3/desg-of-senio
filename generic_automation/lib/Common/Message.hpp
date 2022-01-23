#ifndef __GENERIC_AUTOMATION_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_MESSAGE_HPP__

#include <stdint.h>
#include "StringBuilder.hpp"

namespace genauto {
    /**
     * @brief Abstract message
     */
    class Message {
    public:
        /**
         * @brief Type of the messag id
         */
        typedef uint8_t msgid_t[2];

        /**
         * @brief Simple ctor
         *
         * @param id msg id
         */
        Message();

        /**
         * @brief Checks to see if msgIds are the same
         *
         * @param id to check
         * @return true if ids the same 
         */
        const uint8_t* getMsgId();

        /**
         * @brief Simple to string function written such that no
         * standard library is needed
         *
         * @param buf buffer to store the new string
         * @param size the size of the input buffer
         */
        virtual void toString(StringBuilder& sb);

        static const uint8_t* msgId;
    };
}

// List all message declarations here
static const uint16_t STEPPER_MOTOR_MESSAGE_ID = 1;

#endif