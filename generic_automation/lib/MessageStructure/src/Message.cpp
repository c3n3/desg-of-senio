#include "Message.hpp"
#include "StringBuilder.hpp"

genauto::Message::Message(uint16_t id) : msgId(id)
{}

void genauto::Message::toString(genauto::StringBuilder& sb)
{
    sb.appendString("msgId: ");
    sb.appendInt(msgId);
}

uint16_t genauto::Message::getMsgId()
{
    return msgId;
}