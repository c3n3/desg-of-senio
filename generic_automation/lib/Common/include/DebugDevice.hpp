#ifndef __GENAUTO_DEBUG_DEVICE_HPP__
#define __GENAUTO_DEBUG_DEVICE_HPP__

#include "Device.hpp"
#include "Subscriber.hpp"

namespace genauto {
    class DebugDevice : public Subscriber, public Device {
    public:
        DebugDevice(minor_t minor);

        void execute();
    };
}

#endif
