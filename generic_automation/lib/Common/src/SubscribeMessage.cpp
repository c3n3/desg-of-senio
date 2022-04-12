#include "../include/SubscribeMessage.hpp"
#include "../include/MessageTypeRegistry.hpp"

using namespace genauto;

MESSAGE_ID_UNIQUE(SubscribeMessage);

SubscribeMessage::SubscribeMessage(uint8_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{}

SubscribeMessage::SubscribeMessage()
    : Message(msgSize)
{
    type() = classMsgType;
}

MessageId& SubscribeMessage::idFrom()
{
    return get<MessageId>(idFrom_loc);
}

MessageId& SubscribeMessage::idTo()
{
    return get<MessageId>(idTo_loc);
}

SubscribeMessage::Type& SubscribeMessage::subType()
{
    return get<Type>(subType_loc);
}

