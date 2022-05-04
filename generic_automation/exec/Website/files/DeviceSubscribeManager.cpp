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
    msg.subType() = isAdd ? SubscribeMessage::Sub : SubscribeMessage::RemoveSub;
    msg.idTo() = to;
    msg.idFrom() = from;
    sendTo(&msg);
}

static void espSubUpdatePub(MessageId& to, MessageId& from, bool isAdd)
{
    std::cout << "Connecting " << to.major << " to " << from.major << "\n";
    // Send to the TO
    SubscribeMessage msg;
    msg.idTo() = to;
    msg.idFrom() = from;
    msg.id() = MessageId(from.major, genauto::ConstantIds::Esp::SUB_MANAGER);
    msg.subType() = isAdd ? SubscribeMessage::Pub : SubscribeMessage::RemovePub;
    sendTo(&msg);
}

void DeviceSubscribeManager::removeSub(MessageId& to, MessageId from)
{
    dlog("Disconnecting {0x%x,%d} from {0x%x,%d}\n", to.major, to.minor, from.major, from.minor);

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
            DeviceLoop::loop.removeDevice(dev);
            map.remove(to.major);
        }
    }

    // update the esp devices
    espSubUpdate(to, from, false);
}

void DeviceSubscribeManager::addSub(MessageId& to, MessageId from)
{
    dlog("Connecting {0x%x,%d} to {0x%x,%d}\n", to.major, to.minor, from.major, from.minor);

    if (!map.contains(to.major)) {
        if (map.insert(Pair<major_t, DeviceSubscriber>(to.major, DeviceSubscriber(to.major))) == map.SUCCESS) {
            DeviceLoop::loop.addDevice(&map[to.major+0]);
        } else {
            elog("No space in map\n");
            return;
        }
    } else {
        dlog("Map already contains\n");
    }

    DeviceSubscriber* dev = &map[to.major+0];
    Subscriber* sub = dynamic_cast<Subscriber*>(dev);
    if (sub != nullptr) {
        r.subscribe(sub, from);
        dev->subIncrement();
    } else {
        elog("Sub was null\n");
    }

    // Send messages to sending dev
    espSubUpdate(to, from, true);
}

void DeviceSubscribeManager::removePub(MessageId& to, MessageId from)
{
    dlog("Disconnecting {0x%x,%d} from {0x%x,%d}\n", to.major, to.minor, from.major, from.minor);
    espSubUpdatePub(to, from, false);
}

void DeviceSubscribeManager::addPub(MessageId& to, MessageId from)
{
    dlog("Connecting {0x%x,%d} to {0x%x,%d}\n", to.major, to.minor, from.major, from.minor);
    espSubUpdatePub(to, from, true);
}

DeviceSubscribeManager::Pub DeviceSubscribeManager::pub;

DeviceSubscribeManager::Pub::Pub()
: m(400)
{}

Message* DeviceSubscribeManager::Pub::tryGet()
{
    if (msgs.count()) {
        Buffer b;
        if (msgs.front(b)) {
            m.setBuffer(b.buffer);
            msgs.dequeue();
            return &m;
        }
    }
    return nullptr;
}

void DeviceSubscribeManager::init()
{
    r.addPublisher(&pub);
}

void DeviceSubscribeManager::publish(Message* publish)
{
    pub.msgs.enqueue(publish->getBuffer(), publish->getSizeSafe());
}

