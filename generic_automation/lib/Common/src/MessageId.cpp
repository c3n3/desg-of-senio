#include "../include/Message.hpp"
#include <stdlib.h>
using namespace genauto;

bool MessageId::operator <(const MessageId& other) const
{
    if (major < other.major) {
        return true;
    } else if (other.major < major) {
        return false;
    }
    return minor < other.minor;
}

void MessageId::set(Direction d)
{
    major = (major & (~(0x0001 << DIRECTION_BIT))) | (((uint16_t)d) << DIRECTION_BIT);
}

major_t MessageId::getMajor()
{
    return major;
}

minor_t MessageId::getMinor()
{
    return minor;
}

bool MessageId::operator ==(const MessageId& other)
{
    return major == other.major && minor == other.minor;
}

bool MessageId::operator !=(const MessageId& other)
{
    return !(*this == other);
}

MessageId::MessageId(major_t major, minor_t minor, Direction d)
    : major(), minor(minor)
{
    set(d);
}

MessageId::MessageId() : major(0), minor(0)
{}

MessageId::MessageId(const MessageId& other)
    : major(other.major), minor(other.minor)
{}

MessageId::MessageId(const char* keystring)
{
    // char major[16];
    // char minor[16];
    // const char* it = keystring;
    // int i = 0;
    // // while (*it != ':' && *it != '\0')
    // // {
    // //     major[i++] = *it;
    // //     it++;
    // // }
    // // major[i] = '\0'; 
    // // it++;
    // // i = 0;
    // // while (*it != '\0')
    // // {
    // //     minor[i++] = *it;
    // //     it++;
    // // }
    // // major[i] = '\0'; 
    char* end;
    major = strtol(keystring, &end, 10);
    end++;
    minor = strtol(end, &end, 10);
    dlog("Keystring = %s, %d, %d\n", keystring, major, minor);
}

void MessageId::setMajor(major_t m)
{
    major = m;
}

void MessageId::setMinor(minor_t m)
{
    minor = m;
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
