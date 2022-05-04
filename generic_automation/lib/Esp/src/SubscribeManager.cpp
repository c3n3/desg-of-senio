#include "../include/SubscribeManager.hpp"
#include "../include/CapabilitiesList.hpp"
#include "../../Common/include/SubscribeMessage.hpp"
#include "../include/WifiSender.hpp"

using namespace genauto;

static Subscriber* getSub(minor_t minor)
{
    // Get the correct sub
    auto& list = CapabilitiesList::deviceList;
    for (int i = 0; i < list.getSize(); i++) {
        if (minor == list[i]->minorId) {
            // Add to the router
            auto dev = list[i];
            return dev->sub();
        }
    }
    return nullptr;
}

static Publisher* getPub(minor_t minor)
{
    // Get the correct sub
    auto& list = CapabilitiesList::deviceList;
    for (int i = 0; i < list.getSize(); i++) {
        if (minor == list[i]->minorId) {
            // Add to the router
            auto dev = list[i];
            return dev->pub();
        }
    }
}

void SubscribeManager::addSub(SubscribeMessage* msg)
{
    Subscriber* sub = getSub(msg->idTo().minor);
    if (sub != nullptr) {
        dlog("Subbing %d-%d to %d-%d\n", msg->idTo().major, msg->idTo().minor, msg->idFrom().major, msg->idFrom().minor);
        router.subscribe(sub, msg->idFrom());
    } else {
        elog("Sub was nullptr\n");
    }
}

void SubscribeManager::removeSub(SubscribeMessage* msg)
{
    Subscriber* sub = getSub(msg->idTo().minor);
    if (sub != nullptr) {
        router.removeSubscribe(sub, msg->idFrom());
    } else {
        elog("Sub was nullptr\n");
    }
}

void SubscribeManager::addPub(SubscribeMessage* msg)
{
    // if we are adding a pub, that means the message comes from us
    Publisher* pub = getPub(msg->idFrom().minor);
    if (pub != nullptr) {
        // If this device is not the receiver, then we send out
        if (msg->idTo().major != deviceId) {
            router.subscribe(&WifiSender::sender, msg->idFrom());
        }
        router.addPublisher(pub);
    } else {
        elog("Sub was nullptr\n");
    }
}

void SubscribeManager::removePub(SubscribeMessage* msg)
{
    // if we are removing a pub, that means the message came from us
    Publisher* pub = getPub(msg->idFrom().minor);
    if (pub != nullptr) {
        if (msg->idTo().major != deviceId) {
            router.removeSubscribe(&WifiSender::sender, msg->idFrom());
        }
        router.removePublisher(pub);
    } else {
        elog("Sub was nullptr\n");
    }
}


void SubscribeManager::execute()
{
    Message* m = nextMessage();
    if (m != nullptr && m->type() == SubscribeMessage::classMsgType) {
        SubscribeMessage real(m->getBuffer(), m->getSizeSafe());
        switch (real.subType()) {
            case SubscribeMessage::Sub:dlog("performing SubscribeMessage::Sub\n"); addSub(&real); break;
            case SubscribeMessage::Pub:dlog("performing SubscribeMessage::Pub\n"); addPub(&real); break;
            case SubscribeMessage::RemovePub:dlog("performing SubscribeMessage::RemovePub\n"); removePub(&real); break;
            case SubscribeMessage::RemoveSub:dlog("performing SubscribeMessage::RemoveSub\n"); removeSub(&real); break;
            default: elog("Invalid sub message\n");
        }
    }
}

SubscribeManager::SubscribeManager()
    : Device(genauto::ConstantIds::Esp::SUB_MANAGER)
{}


Router SubscribeManager::router;
SubscribeManager* SubscribeManager::manager = nullptr;

void SubscribeManager::init()
{
    manager = new SubscribeManager();
    MessageId id(deviceId, manager->minorId);
    id.to();
    router.subscribe(manager, id);
}

