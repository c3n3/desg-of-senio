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

void MessageId::set(Direction d)
{
    major_ = (major_ & (~(0x0001 << DIRECTION_BIT))) | (((uint16_t)d) << DIRECTION_BIT);
}

major_t MessageId::getMajor()
{
    return major_;
}

minor_t MessageId::getMinor()
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

MessageId::MessageId(major_t major, minor_t minor, Direction d)
    : major_(), minor_(minor)
{
    set(d);
}

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

MessageId& MessageId::to()
{
    set(To);
    return *this;
}

MessageId& MessageId::from()
{
    set(From);
    return *this;
}
