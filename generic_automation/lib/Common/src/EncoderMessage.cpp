#include "../include/EncoderMessage.hpp"

using namespace genauto;

const Message::msgType_t EncoderMessage::classMsgType = MSG_TYPE('A', 'C');

/**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
EncoderMessage::EncoderMessage(MessageId id, uint16_t value)
    : id(id), value_(value), Message(id, EncoderMessage::classMsgType)
{
}

/**
         * @brief gets the value of the message
         *
         * @return the value of how much the encoder has changed.
         */
uint8_t EncoderMessage::getValue()
{
    return value_;
}

/**
         * @brief Convert to string
         *
         * @param sb
         */
void EncoderMessage::toString(StringBuilder &sb)
{
    sb.appendString("{EncoderMessage; ");
    sb.appendString("Value: ");
    sb.appendFloat(value_);
    sb.appendString(", ");
    id.toString(sb);
    sb.appendChar('}');
}
