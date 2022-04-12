#ifndef __GENAUTO_DEVICE_SUBSCRIBER_HPP__
#define __GENAUTO_DEVICE_SUBSCRIBER_HPP__

#include "../lib/Common/include/Subscriber.hpp"
#include "../lib/Common/include/Device.hpp"

namespace genauto {
    class DeviceSubscriber : public Subscriber , public Device {
        major_t dev_;
        uint16_t subCount_;
    public:

        DeviceSubscriber& operator=(DeviceSubscriber& other);

        void subIncrement();

        void subDecrement();

        uint16_t subCount();

        DeviceSubscriber(major_t deviceNum);
        DeviceSubscriber();

        void execute();
    };
};

#endif
