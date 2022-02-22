// TODO: Make autogen

#include "../include/CapabilitiesList.hpp"
#include "../include/ButtonDevice.hpp"
#include "../include/PwmDevice.hpp"
#include "../include/StepperDevice.hpp"
#include "../../Common/include/Device.hpp"
#include "../../Common/include/Defines.hpp"
#include "../../Common/include/Capabilities.hpp"

using namespace genauto;

constexpr uint8_t TEST_DEVICE_V1_SIZE = 2;
constexpr uint8_t SUBSCRIBER_SIZE = 1;
constexpr uint8_t PUBLISHER_SIZE = 1;

static Capability testDeviceV1Caps[] = {
    Capability(Button, ConstantIds::Esp::NEW_IDS_START),
    Capability(Pwm, ConstantIds::Esp::NEW_IDS_START + 1)
};

CapabilitiesMessage
CapabilitiesList::capabilitiesList(testDeviceV1Caps, ARRSIZE(testDeviceV1Caps));

ButtonDeviceInst<22> button(ConstantIds::Esp::NEW_IDS_START);
PwmDevice pwm(10, 0, ConstantIds::Esp::NEW_IDS_START + 1);

StepperDevice stepper(32, 33,  ConstantIds::Esp::NEW_IDS_START + 2);

static Device* devices[] = {
    (Device*)&button,
    (Device*)&pwm,
    (Device*)&stepper
};

static Subscriber* subscribers[] = {
    (Subscriber*)&pwm,
    (Subscriber*)&stepper
};

static Publisher* publishers[] = {
    (Publisher*)&button
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
}