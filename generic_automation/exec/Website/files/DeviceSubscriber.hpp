#ifndef __GENAUTO_DEVICE_SUBSCRIBER_HPP__
#define __GENAUTO_DEVICE_SUBSCRIBER_HPP__

#include "../lib/Common/include/Subscriber.hpp"
#include "../lib/Common/include/Device.hpp"

namespace genauto {
    class DeviceSubscriber : public Subscriber , public Device {
    public:
        DeviceSubscriber(major_t deviceNum);

        void execute();
    };
};

#endif
