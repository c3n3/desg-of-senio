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

ButtonDeviceInst<5> button1(ConstantIds::Esp::NEW_IDS_START);
ButtonDeviceInst<14> button2(ConstantIds::Esp::NEW_IDS_START + 1);
ButtonDeviceInst<15> button3(ConstantIds::Esp::NEW_IDS_START + 2);

PwmDevice pwm1(21, 0, ConstantIds::Esp::NEW_IDS_START + 3);
PwmDevice pwm2(18, 0, ConstantIds::Esp::NEW_IDS_START + 4);

StepperDevice stepper1(32, 33,  ConstantIds::Esp::NEW_IDS_START + 5);
StepperDevice stepper2(26, 27,  ConstantIds::Esp::NEW_IDS_START + 6);
StepperDevice stepper3(23, 25,  ConstantIds::Esp::NEW_IDS_START + 7);

EncoderDevice encoder1(34, 35, ConstantIds::Esp::NEW_IDS_START + 8);
EncoderDevice encoder2(36, 39, ConstantIds::Esp::NEW_IDS_START + 9);

AnalogDevice analog1(4, ConstantIds::Esp::NEW_IDS_START + 10);
AnalogDevice analog2(13, ConstantIds::Esp::NEW_IDS_START + 11);

SwitchDevice switch1(16, ConstantIds::Esp::NEW_IDS_START + 12);
SwitchDevice switch2(17, ConstantIds::Esp::NEW_IDS_START + 13);

TimedPublisher timed(1000, MessageId(0, ConstantIds::Esp::NEW_IDS_START + 14));

DebugDevice deb(99);

Device* devices[] = {
    (Device*)&deb
};

Subscriber* subscribers[] = {
    (Subscriber*)&stepper1,
    (Subscriber*)&stepper2,
    (Subscriber*)&stepper3,
    (Subscriber*)&pwm1,
    (Subscriber*)&pwm2,
    (Subscriber*)&switch1,
    (Subscriber*)&switch2,
    (Subscriber*)&deb
};

Publisher* publishers[] = {
    (Publisher*)&button1,
    (Publisher*)&button2,
    (Publisher*)&button3,
    (Publisher*)&encoder1,
    (Publisher*)&encoder2,
    (Publisher*)&analog1,
    (Publisher*)&analog2,
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
