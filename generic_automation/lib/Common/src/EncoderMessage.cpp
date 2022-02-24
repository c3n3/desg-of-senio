#include "../include/MessageTypeRegistry.hpp"
#include "../include/EncoderMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

static MessageTypeRegistry<EncoderMessage::classMsgType> r;

/**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
EncoderMessage::EncoderMessage(uint8_t* buffer)
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
int16_t& EncoderMessage::value()
{
    return get<int16_t>(value_location);
}

