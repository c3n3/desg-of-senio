#ifndef __GENERIC_AUTOMATION_PWM_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_PWM_MESSAGE_HPP__

#include "Message.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto {
    /**
     * @brief A stepper motor message
     */
    class PwmMessage : public Message {
        private:
        static constexpr location_t dutyCycle_location = Message::type_loc + sizeof(msgType_t);
        static constexpr location_t onOff_location = dutyCycle_location + sizeof(int16_t);
        static constexpr uint16_t msgSize
            = Message::baseSize + sizeof(int16_t) + sizeof(bool);
    public:

        /**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
        PwmMessage();
        PwmMessage(uint8_t* buffer, uint16_t bufferSize);


        /**
         * @brief 
         * 
         * @return int16_t& 
         */
        int16_t& dutyCycle();


        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool& onOff();


        /**
         * @brief Type of the message specific to class
         */
        static constexpr msgType_t classMsgType = 0x0003;
    };
}

#endif
