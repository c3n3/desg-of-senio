#include "../include/AnalogMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

const msgType_t AnalogMessage::classMsgType = MSG_TYPE('A', 'F');

/**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
AnalogMessage::AnalogMessage(uint8_t* buffer)
    : Message(buffer, msgSize)
{
    if (size_() != msgSize) {
        dlog("Error: buffer size mismatch, watch for segfault.\n");
    }

    // Set type in case this is a new buffer
    Message::type() = classMsgType;
}


/**
         * @brief gets the value of the message
         *
         * @return the value of how much the Pwm has changed.
         */
float& AnalogMessage::value()
{
    return get<float>(value_location);
}


/**
         * @brief Convert to string
         *
         * @param sb
         */
void AnalogMessage::toString(StringBuilder &sb)
{
    sb.appendString("{AnalogMessage; ");
    sb.appendString("Value: ");
    sb.appendFloat(value());
    sb.appendString(", ");
    id().toString(sb);
    sb.appendChar('}');
}