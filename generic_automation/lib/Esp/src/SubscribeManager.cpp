#include "../include/SubscribeManager.hpp"
#include "../include/CapabilitiesList.hpp"
#include "../../Common/include/SubscribeMessage.hpp"

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
        dlog("Got new subscription\n");

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
{
    MessageId id(deviceId, minorId);
    id.to();
    router.subscribe(this, id);
}


Router SubscribeManager::router;
SubscribeManager SubscribeManager::manager;
