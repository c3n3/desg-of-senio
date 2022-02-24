#include "../include/SubscribeMessage.hpp"
#include "../include/MessageTypeRegistry.hpp"

using namespace genauto;

static MessageTypeRegistry<SubscribeMessage::classMsgType> r;

SubscribeMessage::SubscribeMessage(uint8_t* buffer)
    : Message(buffer, msgSize)
{
    if (size_() != msgSize) {
        dlog("Error: buffer size mismatch, watch for segfault.\n");
    }

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
