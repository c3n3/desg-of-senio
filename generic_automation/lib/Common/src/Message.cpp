
#include "../include/Message.hpp"
#include "../include/StringBuilder.hpp"

const genauto::Message::msgType_t genauto::Message::classMsgType = MSG_TYPE('A', 'A');

genauto::Message::Message(const MessageId& id, msgType_t type)
    : id(id), msgType(type)
{}

void genauto::Message::toString(genauto::StringBuilder& sb)
{
    sb.appendString("{ Message: ");
    id.toString(sb);
    sb.appendString(" }");
}

