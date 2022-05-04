#ifndef __GENERIC_AUTOMATION_STEPPER_MOTOR_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_STEPPER_MOTOR_MESSAGE_HPP__

#include "Message.hpp"
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
        enum Mode
        {
            Degrees,
            DegreesSecond
        };

    private:
        static constexpr location_t value_loc = Message::type_loc + sizeof(msgType_t);
        static constexpr location_t valueType_loc = value_loc + sizeof(float);
        static constexpr location_t stepScale_loc = valueType_loc + sizeof(Mode);
        static constexpr location_t force_loc = stepScale_loc + sizeof(float);
        static constexpr uint16_t msgSize = Message::baseSize + sizeof(msgType_t) + sizeof(float) + sizeof(float) + sizeof(Mode);

    public:
        /**
         * @brief Create a stepper motor message
         *
         * @param buffer The buffer for the message
         */
        StepperMotorMessage(uint8_t *buffer, uint16_t bufferSize);
        StepperMotorMessage();

        /**
         * @brief gets the value of the message
         *
         * @return float
         */
        float& value();

        /**
         * @brief 
         * 
         * @return float& 
         */
        float& stepScale();

        /**
         * @brief Force an action and do not stop until done,
         * will ignore all other commands
         */
        bool& force();

        /**
         * @brief Gets the type of the message
         *
         * @return Type
         */
        Mode& modeType();

        /**
         * @brief Type of the message specific to class
         */
        static constexpr msgType_t classMsgType = 0x0005;
    };
}

#endif
