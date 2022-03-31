#include "DeviceLoop.hpp"

DeviceLoop::DeviceLoop()
{
    run();
}

bool DeviceLoop::exec()
{
    devsMutex.lock();
    for (auto& dev : devs) {
        dev->execute();
    }
    devsMutex.unlock();
    return true;
}

void DeviceLoop::addDevice(Device* dev)
{
    devsMutex.lock();
    devs.insert(dev);
    devsMutex.unlock();
}

void DeviceLoop::removeDevice(Device* dev)
{
    devsMutex.lock();
    auto res = devs.find(dev);
    if (res != devs.end()) {
        devs.erase(res);
    } else {
        elog("Invalid removal of device\n");
    }
    devsMutex.unlock();
}
