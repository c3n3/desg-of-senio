#include "DeviceSubscribeManager.hpp"
#include "SubscribeMessage.hpp"
#include "Common.h"

using namespace genauto;

Map<major_t, DeviceSubscriber> DeviceSubscribeManager::map;

Router DeviceSubscribeManager::r;

static void espSubUpdate(MessageId& to, MessageId& from, bool isAdd)
{
    std::cout << "Connecting " << to.major << " to " << from.major << "\n";
    // Send to the TO
    SubscribeMessage msg;
    msg.id().major = to.major;
    msg.id().minor = ConstantIds::Esp::SUB_MANAGER;
    std::cout << "Connecting " << to.major << " to " << from.major << "\n";
    msg.subType() = isAdd ? SubscribeMessage::Sub : SubscribeMessage::RemoveSub;
    std::cout << "Connecting " << to.major << " to " << from.major << "\n";
    msg.idTo() = to;
    std::cout << "Connecting " << to.major << " to " << from.major << "\n";
    msg.idFrom() = from;
    std::cout << "Connecting " << to.major << " to " << from.major << "\n";
    msg.log();
    std::cout << "Connecting " << to.major << " to " << from.major << "\n";
    sendTo(&msg);

    msg.id() = MessageId(from.major, genauto::ConstantIds::Esp::SUB_MANAGER);
    msg.subType() = isAdd ? SubscribeMessage::Pub : SubscribeMessage::RemovePub;
    sendTo(&msg);
}

void DeviceSubscribeManager::removeSub(MessageId& to, MessageId from)
{
    if (map.contains(to.major)) {
        DeviceSubscriber* dev = &map[to.major+0];
        Subscriber* sub = dynamic_cast<Subscriber*>(dev);
        if (sub != nullptr) {
            r.removeSubscribe(sub, from);
            dev->subDecrement();
        } else {
            elog("Sub was nullptr\n");
        }
        if (dev->subCount() == 0) {
            loop.removeDevice(dev);
            map.remove(to.major);
        }
    }

    // update the esp devices
    espSubUpdate(to, from, false);
}

void DeviceSubscribeManager::addSub(MessageId& to, MessageId from)
{
    std::cout << "Connecting " << to.major << " to " << from.major << "\n";
    if (!map.contains(to.major)) {
        if (map.insert(Pair<major_t, DeviceSubscriber>(to.major, DeviceSubscriber(to.major))) == map.SUCCESS) {
            loop.addDevice(&map[to.major+0]);
        } else {
            return;
        }
    }

    DeviceSubscriber* dev = &map[to.major+0];
    Subscriber* sub = dynamic_cast<Subscriber*>(dev);
    if (sub != nullptr) {
        r.subscribe(sub, from);
        dev->subIncrement();
    } else {
        elog("Sub was null\n");
    }

    // Send messages to sending dev and receiving dev
    espSubUpdate(to, from, true);
}

DeviceLoop DeviceSubscribeManager::loop;
