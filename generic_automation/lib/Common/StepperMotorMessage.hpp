#ifndef __GENERIC_AUTOMATION_STEPPER_MOTOR_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_STEPPER_MOTOR_MESSAGE_HPP__

#include "Message.hpp"
#include "StringBuilder.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto {
    /**
     * @brief A stepper motor message
     */
    class StepperMotorMessage : public Message {
    public:
        /**
         * @brief Allows us to specify if we are instructing a degree change
         * or setting a speed
         */
        enum Type {
            Speed,
            Degree
        };

        /**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
        StepperMotorMessage(MessageId id, Type type, float value);

        /**
         * @brief gets the value of the message
         *
         * @return float
         */
        float getValue();

        /**
         * @brief Gets the type of the message
         *
         * @return Type
         */
        Type getType();

        /**
         * @brief Convert to string
         *
         * @param sb
         */
        void toString(StringBuilder& sb);
        
        /**
         * @brief Type of the message specific to class
         */
        static const Message::msgType_t msgType;
    private:
        Type type_;
        float value_;
    };
}

#endif
