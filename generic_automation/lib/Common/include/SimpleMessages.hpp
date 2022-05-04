#ifndef __GENERIC_AUTOMATION_SIMPLE_MESSAGES_HPP__
#define __GENERIC_AUTOMATION_SIMPLE_MESSAGES_HPP__

#include "Message.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto {
    /**
     * @brief A stepper motor message
     */
    class FlipMessage : public Message {
        private:
        static constexpr location_t on_location = Message::type_loc + sizeof(msgType_t);
        static constexpr uint16_t msgSize = Message::baseSize + sizeof(bool);
    public:

        /**
         * @brief Construct a new Switch Message object
         * 
         * @param buffer 
         */
        FlipMessage(uint8_t* buffer, uint16_t bufferSize);
        FlipMessage();

        /**
         * @brief If on
         */
        bool& on();

        /**
         * @brief Type of the message specific to class
         */
        static constexpr msgType_t classMsgType = 0x0008;
    };

    /**
     * @brief A stepper motor message
     */
    class IncrementMessage : public Message {
        private:
        static constexpr location_t increment_location = Message::derivedStart_loc;
        static constexpr uint16_t msgSize = Message::baseSize + sizeof(int16_t);
    public:

        /**
         * @brief Construct a new Switch Message object
         *
         * @param buffer 
         */
        IncrementMessage(uint8_t* buffer, uint16_t bufferSize);
        IncrementMessage();

        /**
         * @brief If on
         */
        int16_t& increment();

        /**
         * @brief Type of the message specific to class
         */
        static constexpr msgType_t classMsgType = 0x0009;
    };
}

#endif
