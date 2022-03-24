// TODO: Make autogen

#include "../include/CapabilitiesList.hpp"
#include "../include/ButtonDevice.hpp"
#include "../include/PwmDevice.hpp"
#include "../include/StepperDevice.hpp"
#include "../include/TimedPublisher.hpp"
#include "../../Common/include/Device.hpp"
#include "../../Common/include/DebugDevice.hpp"
#include "../../Common/include/Defines.hpp"
#include "../../Common/include/Capabilities.hpp"
#include "../include/config.hpp"

#include <WiFi.h>

using namespace genauto;

constexpr uint8_t TEST_DEVICE_V1_SIZE = 2;

Capability testDeviceV1Caps[] = {
    Capability(Pwm, 9),
    Capability(Button, 10),
};

CapabilitiesMessage*
CapabilitiesList::capabilitiesList = nullptr;

ButtonDeviceInst<22> button(ConstantIds::Esp::NEW_IDS_START);
PwmDevice pwm(13, 0, ConstantIds::Esp::NEW_IDS_START + 1);

StepperDevice stepper(32, 33,  ConstantIds::Esp::NEW_IDS_START + 2);

TimedPublisher timed(1000, MessageId(0, ConstantIds::Esp::NEW_IDS_START + 2));

DebugDevice deb(99);

Device* devices[] = {
    (Device*)&deb
};

Subscriber* subscribers[] = {
    (Subscriber*)&deb,
};

Publisher* publishers[] = {
    (Publisher*)&button,
    (Publisher*)&timed
};

StaticList<Subscriber*> CapabilitiesList::subscriberList(
    subscribers, ARRSIZE(subscribers));

StaticList<Publisher*> CapabilitiesList::publisherList(
    publishers, ARRSIZE(publishers));

StaticList<Device*> CapabilitiesList::deviceList(
    devices, ARRSIZE(devices));

void CapabilitiesList::init()
{
    // Add all subscribers to the router
    // All devices will subscribe to messages to themselves
    capabilitiesList = new CapabilitiesMessage(testDeviceV1Caps, ARRSIZE(testDeviceV1Caps));
    capabilitiesList->ip() = WiFi.localIP();
}
