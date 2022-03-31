#ifndef __GENAUTO_DEVICE_LOOP_HPP__
#define __GENAUTO_DEVICE_LOOP_HPP__

#include "../lib/Common/include/Device.hpp"
#include "../lib/Common/include/MessageId.hpp"
#include "Thread.hpp"
#include <set>
#include <mutex>

namespace genauto {
    class DeviceLoop : public Thread {
        std::set<Device*> devs;

        std::mutex devsMutex;
    public:
        DeviceLoop();

        bool exec();

        void addDevice(Device* dev);

        void removeDevice(Device* dev);
    };
};

#endif
