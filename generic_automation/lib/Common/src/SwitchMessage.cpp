#include "../include/MessageTypeRegistry.hpp"
#include "../include/SwitchMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

MESSAGE_ID_UNIQUE(SwitchMessage);

/**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
SwitchMessage::SwitchMessage(uint8_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{}

SwitchMessage::SwitchMessage()
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
bool& SwitchMessage::on()
{
    return get<bool>(on_location);
}
