#include "../include/DebugDevice.hpp"



DebugDevice::DebugDevice(minor_t minor)
    : Device(minor), t("DebugDevice"), prev(0)
{
    dlog("Created debug device with id: %d\n", minor);
}

void DebugDevice::execute()
{
    Message* msg = nextMessage();

    if (msgs_.count() == msgs_.size()) {
        dlog("Out of message space\n");
    }
    if (msg != nullptr) {
        dlog("Debug device %d got message: \n", minorId);
        msg->log();
    }
}

Message* DebugDevice::tryGet()
{
    // So we do not spam messages
    if (t.msTime() - prev > 5000) {
        prev = t.msTime();
        // return &msg;
    }
    return nullptr;
}

Subscriber* DebugDevice::sub()
{
    return static_cast<Subscriber*>(this);
}

Publisher* DebugDevice::pub()
{
    return static_cast<Publisher*>(this);
}


