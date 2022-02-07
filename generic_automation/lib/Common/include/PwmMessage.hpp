#ifndef __GENERIC_AUTOMATION_PWM_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_PWM_MESSAGE_HPP__

#include "Message.hpp"
#include "StringBuilder.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto {
    /**
     * @brief A stepper motor message
     */
    class PwmMessage : public Message {
        private:
        static const uint16_t dutyCycle_location = type_location + sizeof(uint16_t);
        static const uint16_t onOff_location = dutyCycle_location + sizeof(bool);
    public:

        /**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
        PwmMessage(MessageId id, int16_t dutyCycle, bool onOff);

        /**
         * @brief gets the value of the message
         *
         * @return uint16_t
         */
        uint16_t getDutyCycle();

        /**
         * @brief Set the Value object
         * 
         * @param value 
         */
        void setDutyCycle(int16_t dutyCycle);


        /**
         * @brief gets the value of the message
         *
         * @return uint16_t
         */
        bool getOnOff();

        /**
         * @brief Set the Value object
         * 
         * @param value 
         */
        void setOnOff(bool onOff);


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
        int16_t dutyCycle_;
        bool onOff_;
    };
}

#endif
