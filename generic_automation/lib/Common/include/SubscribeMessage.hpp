#ifndef __GENAUTO_SUBSCRIBE_MESSAGE_HPP__
#define __GENAUTO_SUBSCRIBE_MESSAGE_HPP__

#include "Message.hpp"
#include "StringBuilder.hpp"
#include "MessageId.hpp"

#include <stdint.h>

namespace genauto
{
    /**
     * @brief A stepper motor message
     */
    class SubscribeMessage : public Message
    {
    private:
        static constexpr location_t idFrom_loc = Message::dirivedStart_loc;
        static constexpr location_t idTo_loc = idFrom_loc + sizeof(MessageId);

        static constexpr uint16_t msgSize
            = Message::baseSize + sizeof(MessageId) + sizeof(MessageId);
    public:
        /**
         * @brief Create a stepper motor message
         *
         * @param buffer The buffer for the message
         */
        SubscribeMessage(uint8_t* buffer = nullptr);

        /**
         * @brief Tells what id will come from
         *
         * @return float
         */
        MessageId& idFrom();

        /**
         * @brief Tells who should subscribe
         *
         * @return float
         */
        MessageId& idTo();

        /**
         * @brief Convert to string
         *
         * @param sb
         */
        void toString(StringBuilder &sb);

        /**
         * @brief Type of the message specific to class
         */
        static const msgType_t classMsgType = MSG_TYPE('A', 'D');
    };
}

#endif
