#include "../include/Message.hpp"
#include "../include/MessageTypeRegistry.hpp"

using namespace genauto;

Message::Message(uint16_t size)
    : alloc(true),
      bufferSize_(size)
{
    if (size < baseSize) {
        elog("Message size less than base size\n");
    }
    dlog("Alloc %d\n", size);
    buffer_ = new uint8_t[size];
    memset(buffer_, 0, size);
    alloc = true;
    size_() = size;
}

Message::Message(uint8_t* buffer, uint16_t bufferSize)
    : buffer_(buffer),
      bufferSize_(bufferSize),
      alloc(false)
{
    setBuffer(buffer);
}

Message::Message (const Message& other)
    : buffer_(nullptr),
      alloc(false),
      bufferSize_(other.bufferSize_)
{
    setBuffer(other.getBuffer());
}

uint16_t Message::getBufferSize()
{
    return bufferSize_;
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
    dlog("Message: id = {%x,%d}, type = %x, size=%d\n", id().getMajor(), id().getMinor(), type(), size());
}