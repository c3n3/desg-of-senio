#include "../include/DebugDevice.hpp"



DebugDevice::DebugDevice(minor_t minor)
    : Device(minor)
{
    dlog("Created debug device with id: %d\n", minor);
}

void DebugDevice::execute()
{
    Message* msg = nextMessage();

    if (msg != nullptr) {
        dlog("Debug device %d got message: \n", minorId);
        msg->log();
    }
}
