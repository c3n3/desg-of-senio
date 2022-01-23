
#include "Message.hpp"
#include "StringBuilder.hpp"

const uint8_t* genauto::Message::msgId = (uint8_t*)"AA";

genauto::Message::Message()
{}

void genauto::Message::toString(genauto::StringBuilder& sb)
{
    sb.appendString("msgId: ");
    sb.appendString((char*)msgId);
}

const uint8_t* genauto::Message::getMsgId()
{
    return msgId;
}
