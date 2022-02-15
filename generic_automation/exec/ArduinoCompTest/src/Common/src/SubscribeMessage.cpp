#include "../include/SubscribeMessage.hpp"

using namespace genauto;

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

void SubscribeMessage::toString(StringBuilder &sb)
{
    sb.appendString("{SubscribeMessage; Type: ");
    sb.appendString("From: ");
    idFrom().toString(sb);
    sb.appendString(" To: ");
    idTo().toString(sb);
    sb.appendString(", ");
    id().toString(sb);
    sb.appendChar('}');
}
