#include "../include/MessageTypeRegistry.hpp"
#include "../include/AnalogMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

static MessageTypeRegistry<AnalogMessage::classMsgType> r;

/**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
AnalogMessage::AnalogMessage(uint8_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{}

AnalogMessage::AnalogMessage()
    : Message(msgSize)
{
    type() = classMsgType;
}


/**
         * @brief gets the value of the message
         *
         * @return the value of how much the Pwm has changed.
         */
uint16_t& AnalogMessage::value()
{
    return get<uint16_t>(value_location);
}
