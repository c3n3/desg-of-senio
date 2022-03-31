
#include "DeviceSubscriber.hpp"
#include "Common.h"
#include "../database/Database.hpp"

DeviceSubscriber::DeviceSubscriber(major_t deviceNum)
    : Device(0), dev_(deviceNum)
{}

DeviceSubscriber::DeviceSubscriber()
    : Device(0), dev_(0)
{}

void DeviceSubscriber::execute()
{
    Message* msg = nextMessage();
    if (msg != nullptr) {
        dlog("Sending message to %d\n", dev_);
        send(msg, dev_);
    }
}

void DeviceSubscriber::subIncrement()
{
    subCount_++;
}

void DeviceSubscriber::subDecrement()
{
    if (subCount_ != 0) {
        subCount_--;
    }
}

uint16_t DeviceSubscriber::subCount()
{
    return subCount_;
}

DeviceSubscriber& DeviceSubscriber::operator=(DeviceSubscriber& other)
{
    dev_ = other.dev_;
    subCount_ = other.subCount_;
    return *this;
}
