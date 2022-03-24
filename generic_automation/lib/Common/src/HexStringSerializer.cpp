#include "../include/HexStringSerializer.hpp"

using namespace genauto;

HexStringSerializer::HexStringSerializer(int maxSize)
    : bufferIdx_(0), maxSize_(maxSize), currentSize_(0)
{
    buffer_ = new char[maxSize_];
}

HexStringSerializer::~HexStringSerializer()
{
    delete[] buffer_;
}

HexStringSerializer::Result HexStringSerializer::serialize(Message* msg)
{
    if (msg->size()*2 + 1 > maxSize_) {
        elog("Improper message size\n");
        return Failure;
    }
    uint8_t* serial = msg->getBuffer();
    int index = 0;
    // Iterate over bytes
    for (int i = 0; i < msg->size(); i++) {
        // Iterate over 4 bits (hex)
        for (int hexIdx = 0; hexIdx < 2; hexIdx++) {
            uint8_t hex = (serial[i] >> (hexIdx * 4)) & 0x0F;
            buffer_[index++] = 'A' + hex;
        }
    }
    buffer_[index] = '\0';
    currentSize_ = msg->size()*2;

    return Success;
}

HexStringSerializer::Result HexStringSerializer::parse(const uint8_t* incoming, size_t size)
{
    int byteOn = 0;
    if (size > maxSize_ - bufferIdx_) {
        dlog("Message size too large. Max=%d, Got=%d\n", maxSize_, size);
        return Failure;
    }
    for (int i = 0; i < size; i++) {
        buffer_[bufferIdx_++] = incoming[i];
        currentSize_ = bufferIdx_;
    }
    bufferIdx_ = 0;
}

void HexStringSerializer::cancelParse()
{
    bufferIdx_ = 0;
    currentSize_ = 0;
}

HexStringSerializer::Result HexStringSerializer::deserialize(Message* msg)
{
    if (msg == nullptr) {
        elog("Error: msg was null");
        return Failure;
    }
    uint8_t* buffer = msg->getBuffer();
    for (int i = 0; i < msg->getBufferSize()*2 && i < currentSize_; i += 2) {
        uint8_t byteTwo = ((buffer_[i + 1] - 'A')) << 4;
        uint8_t byteOne = ((buffer_[i] - 'A'));
        buffer[(i / 2)] = byteTwo | byteOne;
    }
    return Success;
}

HexStringSerializer::Result HexStringSerializer::validate(const uint8_t* buf, size_t size)
{
    return Success;
}

const char* HexStringSerializer::getBuffer()
{
    return buffer_;
}

size_t HexStringSerializer::maxSize()
{
    return maxSize_;
}

size_t HexStringSerializer::currentSize()
{
    return currentSize_;
}
