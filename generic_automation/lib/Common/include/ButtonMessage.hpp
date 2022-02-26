#ifndef __GENERIC_AUTOMATION_BUTTON_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_BUTTON_MESSAGE_HPP__

#include "Message.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto {
    /**
     * @brief A stepper motor message
     */
    class ButtonMessage : public Message {
        private:
        static constexpr location_t pressed_location = Message::type_loc + sizeof(msgType_t);
        static constexpr uint16_t msgSize = Message::baseSize + sizeof(bool);
    public:

        /**
         * @brief Construct a new Button Message object
         * 
         * @param buffer 
         */
        ButtonMessage(uint8_t* buffer, uint16_t bufferSize);
        ButtonMessage();

        /**
         * @brief 
         * 
         * @return uint16_t& 
         */
        bool& pressed();

        /**
         * @brief Type of the message specific to class
         */
        static constexpr msgType_t classMsgType = 0x0004;
    };
}

#endif
