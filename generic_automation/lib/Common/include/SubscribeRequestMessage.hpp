#ifndef __GENAUTO_SUBSCRIBE_REQUEST_MESSAGE_HPP__
#define __GENAUTO_SUBSCRIBE_REQUEST_MESSAGE_HPP__

#include "Message.hpp"
#include "StringBuilder.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto
{
    /**
     * @brief A stepper motor message
     */
    class PublishMessage : public Message
    {
    private:
        static constexpr location_t value_loc = Message::type_loc + sizeof(msgType_t);
        static constexpr location_t valueType_loc = value_loc + sizeof(float);
        static constexpr uint16_t msgSize
            = Message::baseSize + sizeof(Type) + sizeof(float);
    public:

        /**
         * @brief Create a stepper motor message
         *
         * @param buffer The buffer for the message
         */
        StepperMotorMessage(uint8_t* buffer = nullptr);

        /**
         * @brief gets the value of the message
         *
         * @return float
         */
        float& value();


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

        operator Message()
        {
            dlog("TEST\n");
            return Message(getBuffer());
        }
    };
}

#endif
