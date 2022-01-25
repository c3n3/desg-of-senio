
#include "Message.hpp"
#include "StringBuilder.hpp"

const genauto::Message::msgType_t genauto::Message::msgType = {'A', 'A'};

genauto::Message::Message(const MessageId& id)
    : id(id)
{}

void genauto::Message::toString(genauto::StringBuilder& sb)
{
    sb.appendString("{ Message: ");
    id.toString(sb);
    sb.appendString(" }");
}

