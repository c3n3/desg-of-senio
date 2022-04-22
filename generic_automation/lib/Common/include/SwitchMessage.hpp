#ifndef __GENERIC_AUTOMATION_SWITCH_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_SWITCH_MESSAGE_HPP__

#include "Message.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto {
    /**
     * @brief A stepper motor message
     */
    class SwitchMessage : public Message {
        private:
        static constexpr location_t on_location = Message::type_loc + sizeof(msgType_t);
        static constexpr uint16_t msgSize = Message::baseSize + sizeof(bool);
    public:

        /**
         * @brief Construct a new Switch Message object
         * 
         * @param buffer 
         */
        SwitchMessage(uint8_t* buffer, uint16_t bufferSize);
        SwitchMessage();

        /**
         * @brief If on
         */
        bool& on();

        /**
         * @brief Type of the message specific to class
         */
        static constexpr msgType_t classMsgType = 0x0007;
    };
}

#endif
