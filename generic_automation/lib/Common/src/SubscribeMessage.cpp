#include "../include/SubscribeMessage.hpp"
#include "../include/MessageTypeRegistry.hpp"

using namespace genauto;

MESSAGE_ID_UNIQUE(SubscribeMessage);

SubscribeMessage::SubscribeMessage(uint8_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{
    // Set type in case this is a new buffer
    Message::type() = classMsgType;
}

MessageId& SubscribeMessage::idFrom()
{
    return get<MessageId>(idFrom_loc);
}

MessageId& SubscribeMessage::idTo()
{
    return get<MessageId>(idTo_loc);
}
