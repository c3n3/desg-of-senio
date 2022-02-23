// TODO: Make autogen

#include "../include/CapabilitiesList.hpp"
#include "../include/ButtonDevice.hpp"
#include "../include/PwmDevice.hpp"
#include "../include/StepperDevice.hpp"
#include "../include/TimedPublisher.hpp"
#include "../../Common/include/Device.hpp"
#include "../../Common/include/Defines.hpp"
#include "../../Common/include/Capabilities.hpp"
#include "../include/config.hpp"

using namespace genauto;

constexpr uint8_t TEST_DEVICE_V1_SIZE = 2;

static Capability testDeviceV1Caps[] = {
    Capability(Button, ConstantIds::Esp::NEW_IDS_START),
    Capability(Pwm, ConstantIds::Esp::NEW_IDS_START + 1)
};

// CapabilitiesMessage
// CapabilitiesList::capabilitiesList(testDeviceV1Caps, 0);

ButtonDeviceInst<22> button(ConstantIds::Esp::NEW_IDS_START);
PwmDevice pwm(26, 0, ConstantIds::Esp::NEW_IDS_START + 1);

StepperDevice stepper(32, 33,  ConstantIds::Esp::NEW_IDS_START + 2);

TimedPublisher timed(1000, MessageId(DEVICE_ID, ConstantIds::Esp::NEW_IDS_START + 2));

Device* devices[] = {
    (Device*)&button,
    (Device*)&pwm,
    (Device*)&stepper
};

Subscriber* subscribers[] = {
    (Subscriber*)&pwm,
    (Subscriber*)&stepper
};

Publisher* publishers[] = {
    (Publisher*)&button,
    (Publisher*)&timed
};

StaticList<Subscriber*> CapabilitiesList::subscriberList(
    subscribers, 2);

StaticList<Publisher*> CapabilitiesList::publisherList(
    publishers, 2);

StaticList<Device*> CapabilitiesList::deviceList(
    devices, 3);


void CapabilitiesList::init()
{
    // Add all subscribers to the router
    // All devices will subscribe to messages to themselves
}