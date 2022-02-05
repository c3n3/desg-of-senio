#include "../include/Message.hpp"

using namespace genauto;

Message::Message(uint8_t* buffer, uint16_t size)
    :   buffer_(buffer),
        alloc(false)
{
    if (buffer == nullptr) {
        dlog("Alloc %d\n", size);
        buffer_ = new uint8_t[size];
        memset(buffer_, 0, size);
        setBuffer(buffer);
        alloc = true;
        size_() = size;
    } else {
        setBuffer(buffer);
    }
}

Message::~Message()
{
    if (alloc) {
        dlog("De-alloc %d\n", *size_);
        delete[] buffer_;
    }
}

uint16_t Message::getSize()
{
    return size_();
}

MessageId& Message::id()
{
    return id_();
}

uint8_t* Message::getBuffer()
{
    return buffer_;
}

uint16_t& Message::type()
{
    return type_();
}


void Message::toString(StringBuilder& sb)
{
    sb.appendString("{Message: [id: ");
    id_().toString(sb);
    sb.appendString("], [size: ");
    sb.appendInt(getSize());
    sb.appendString("], [type: ");
    sb.appendInt(type());
    sb.appendString("]}");
}

void Message::setBuffer(uint8_t* buffer)
{
    if (alloc) {
        delete[] buffer_;
        dlog("De-alloc %d\n", *size_);
        alloc = false;
    }
    buffer_ = buffer;
}