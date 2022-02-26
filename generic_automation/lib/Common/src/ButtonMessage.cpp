#include "../include/MessageTypeRegistry.hpp"
#include "../include/ButtonMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

static MessageTypeRegistry<ButtonMessage::classMsgType> r;

/**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
ButtonMessage::ButtonMessage(uint8_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{}

ButtonMessage::ButtonMessage()
    : Message(msgSize)
{
    // Set type in case this is a new buffer
    Message::type() = classMsgType;
}


/**
         * @brief gets the value of the message
         *
         * @return the value of how much the Pwm has changed.
         */
bool& ButtonMessage::pressed()
{
    return get<bool>(pressed_location);
}
