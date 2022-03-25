#include "../include/SubscribeManager.hpp"
#include "../include/CapabilitiesList.hpp"
#include "../../Common/include/SubscribeMessage.hpp"

using namespace genauto;

void SubscribeManager::execute()
{
    Message* m = nextMessage();
    if (m != nullptr && m->type() == SubscribeMessage::classMsgType) {
        SubscribeMessage real(m->getBuffer(), m->getSizeSafe());
        dlog("Got new subscription\n");

        // Get the correct sub
        auto& list = CapabilitiesList::deviceList;
        for (int i = 0; i < list.getSize(); i++) {
            if (real.idTo().minor == list.getList()[i]->minorId) {
                // Add to the router
                //devRouter_->Subscribe((Subscriber*)list.getList()[i], real.idTo());
            }
        }
    }
}

SubscribeManager::SubscribeManager(minor_t minor, Router* devRouter)
    : Device(minor), devRouter_(devRouter)
{
    MessageId id(deviceId, SubscribeMessage::SUB_MINOR_ID);
    //devRouter_->Subscribe(this, id);
}
