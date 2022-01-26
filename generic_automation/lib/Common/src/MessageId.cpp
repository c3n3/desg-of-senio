#include "../include/Message.hpp"

using namespace genauto;

bool MessageId::operator <(const MessageId& other)
{
    if (major < other.major) {
        return true;
    } else if (other.major < major) {
        return false;
    }
    return minor < other.minor;
}

bool MessageId::operator ==(const MessageId& other)
{
    return major == other.major && minor == other.minor;
}

bool MessageId::operator !=(const MessageId& other)
{
    return !(*this == other);
}

MessageId::MessageId(uint16_t major, uint8_t minor)
    : major(major), minor(minor)
{}

MessageId::MessageId(const MessageId& other)
    : major(other.major), minor(other.minor)
{}

void MessageId::toString(StringBuilder& sb) const
{
    sb.appendString("{ MessageId M: ");
    sb.appendInt(major);
    sb.appendString(", m: ");
    sb.appendInt(minor);
    sb.appendString(" }");
}
