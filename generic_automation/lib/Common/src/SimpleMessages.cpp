#include "../include/MessageTypeRegistry.hpp"
#include "../include/SimpleMessages.hpp"
#include "../include/Log.hpp"

using namespace genauto;
MESSAGE_ID_UNIQUE(FlipMessage);

genauto::FlipMessage::FlipMessage(uint8_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{}

genauto::FlipMessage::FlipMessage()
    : Message(msgSize)
{
    // Set type in case this is a new buffer
    Message::type() = classMsgType;
}

bool& genauto::FlipMessage::on()
{
    return get<bool>(on_location);
}

static genauto::MessageTypeRegistry<IncrementMessage::classMsgType> r2;

IncrementMessage::IncrementMessage(uint8_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{}

IncrementMessage::IncrementMessage()
    : Message(msgSize)
{
    Message::type() = classMsgType;
}

int16_t& IncrementMessage::increment()
{
    return get<int16_t>(increment_location);
}
