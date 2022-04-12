#ifndef __GENAUTO_DEBUG_DEVICE_HPP__
#define __GENAUTO_DEBUG_DEVICE_HPP__

#include "Device.hpp"
#include "Subscriber.hpp"
#include "Publisher.hpp"
#include "ButtonMessage.hpp"
#include "Timer.hpp"

namespace genauto {
    class DebugDevice : public Subscriber, public Device, public Publisher {
        ButtonMessage msg;
        Timer t;
        msTimer_t prev;
    public:
        DebugDevice(minor_t minor);

        void execute();

        Message* tryGet();

        Subscriber* sub();
        Publisher* pub();
    };
}

#endif
