#ifndef __GENERIC_AUTOMATION_STEPPER_MOTOR_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_STEPPER_MOTOR_MESSAGE_HPP__

#include "Message.hpp"
#include "StringBuilder.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto
{
    /**
     * @brief A stepper motor message
     */
    class StepperMotorMessage : public Message
    {
    public:
        /**
         * @brief Allows us to specify if we are instructing a degree change
         * or setting a speed
         */
        enum Type
        {
            Speed,
            Degree
        };

    private:
        static constexpr location_t value_loc = Message::type_loc + sizeof(msgType_t);
        static constexpr location_t valueType_loc = value_loc + sizeof(float);
        static constexpr location_t direction_loc = valueType_loc + sizeof(Type);
        static constexpr uint16_t msgSize = Message::baseSize + sizeof(msgType_t) + sizeof(float) + sizeof(Type);

    public:
        /**
         * @brief Create a stepper motor message
         *
         * @param buffer The buffer for the message
         */
        StepperMotorMessage(uint8_t *buffer = nullptr);

        /**
         * @brief gets the value of the message
         *
         * @return float
         */
        float& value();

        /**
         * @brief
         *
         * @return uint8_t
         */
        uint8_t& direction();

        /**
         * @brief Gets the type of the message
         *
         * @return Type
         */
        Type& valueType();

        /**
         * @brief Convert to string
         *
         * @param sb
         */
        void toString(StringBuilder &sb);

        /**
         * @brief Type of the message specific to class
         */
        static const msgType_t classMsgType;
    };
}

#endif
