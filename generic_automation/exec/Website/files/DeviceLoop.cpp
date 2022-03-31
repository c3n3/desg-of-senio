#include "DeviceLoop.hpp"

DeviceLoop::DeviceLoop()
{

}

bool DeviceLoop::exec()
{
    for (auto& dev : devs) {
        dev->execute();
    }
}

void DeviceLoop::addDevice(Device* dev)
{
    
    devs.insert(dev);
}

void DeviceLoop::removeDevice(Device* dev)
{
    auto res = devs.find(dev);
    if (res != devs.end()) {
        devs.erase(res);
    } else {
        elog("Invalid removal of device\n");
    }
}
