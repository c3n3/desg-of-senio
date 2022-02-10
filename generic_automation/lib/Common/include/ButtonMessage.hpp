#ifndef __GENERIC_AUTOMATION_BUTTON_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_BUTTON_MESSAGE_HPP__

#include "Message.hpp"
#include "StringBuilder.hpp"
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
        ButtonMessage(uint8_t* buffer = nullptr);

        /**
         * @brief 
         * 
         * @return uint16_t& 
         */
        bool& pressed();

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