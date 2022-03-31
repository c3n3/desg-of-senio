#include "../lib/Common/include/Device.hpp"
#include "../lib/Common/include/MessageId.hpp"
#include "DeviceLoop.hpp"
#include <set>

using namespace genauto;


void DeviceLoop::addDevice(Device* dev)
{
    devsMutex.lock();
    devs.insert(dev);
    devsMutex.unlock();
}

void DeviceLoop::removeDevice(Device* dev)
{
    devsMutex.lock();
    devs.erase(dev);
    devsMutex.unlock();
}


bool DeviceLoop::exec()
{
    devsMutex.lock();
    for (auto& dev : devs) {
        dev->execute();
    }
    devsMutex.unlock();
}

DeviceLoop::DeviceLoop()
{
    run();
}
