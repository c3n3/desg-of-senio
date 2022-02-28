#include "../include/MessageTypeRegistry.hpp"
#include "../include/EncoderMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

MESSAGE_ID_UNIQUE(EncoderMessage);

/**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
EncoderMessage::EncoderMessage(uint8_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{}

EncoderMessage::EncoderMessage()
    : Message(msgSize)
{
    type() = classMsgType;
}


/**
         * @brief gets the value of the message
         *
         * @return the value of how much the Pwm has changed.
         */
int16_t& EncoderMessage::value()
{
    return get<int16_t>(value_location);
}

