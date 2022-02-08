#include "../include/Message.hpp"

using namespace genauto;

bool MessageId::operator <(const MessageId& other)
{
    if (major_ < other.major_) {
        return true;
    } else if (other.major_ < major_) {
        return false;
    }
    return minor_ < other.minor_;
}

uint16_t MessageId::getMajor()
{
    return major_;
}

uint8_t MessageId::getMinor()
{
    return minor_;
}

bool MessageId::operator ==(const MessageId& other)
{
    return major_ == other.major_ && minor_ == other.minor_;
}

bool MessageId::operator !=(const MessageId& other)
{
    return !(*this == other);
}

MessageId::MessageId(uint16_t major, uint8_t minor, Direction d)
    : major_(
        (major & (~(0x0001 << DIRECTION_BIT))) | (((uint16_t)d) << DIRECTION_BIT)
        ), minor_(minor)
{}

MessageId::MessageId() : major_(0), minor_(0)
{}

MessageId::MessageId(const MessageId& other)
    : major_(other.major_), minor_(other.minor_)
{}

void MessageId::toString(StringBuilder& sb) const
{
    sb.appendString("{ MessageId M: ");
    sb.appendInt(major_);
    sb.appendString(", m: ");
    sb.appendInt(minor_);
    sb.appendString(" }");
}
