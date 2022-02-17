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
        alloc = true;
        size_() = size;
    } else {
        setBuffer(buffer);
    }
}

Message::Message (const Message& other)
    : buffer_(nullptr), 
      alloc(false)
{
    dlog("Vis?\n");
    setBuffer(other.getBuffer());
}

Message::~Message()
{
    if (alloc) {
        dlog("De-alloc %d\n", size_());
        delete[] buffer_;
    }
}

msgSize_t& Message::size_()
{
    return get<msgSize_t>(size_loc);
}

MessageId& Message::id()
{
    return get<MessageId>(id_loc);
}

msgType_t& Message::type()
{
    return get<msgType_t>(type_loc);
}

msgSize_t Message::size()
{
    return size_();
}

uint8_t* Message::getBuffer() const
{
    return buffer_;
}

void Message::toString(StringBuilder& sb)
{
    sb.appendString("{Message: [id: ");
    id().toString(sb);
    sb.appendString("], [size: ");
    sb.appendInt(size());
    sb.appendString("], [type: ");
    sb.appendInt(type());
    sb.appendString("]}");
}

void Message::setBuffer(uint8_t* buffer)
{
    if (alloc) {
        delete[] buffer_;
        dlog("De-alloc %d\n", size_());
        alloc = false;
    }
    buffer_ = buffer;
}

void Message::log()
{
    StringBuilder sb(1000);
    toString(sb);
    dlog("%s\n", sb.getString());
}