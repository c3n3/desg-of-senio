// TODO: Make autogen

#include "../include/CapabilitiesList.hpp"
#include "../include/ButtonDevice.hpp"
#include "../include/PwmDevice.hpp"
#include "../include/StepperDevice.hpp"
#include "../include/SwitchDevice.hpp"
#include "../include/AnalogDevice.hpp"
#include "../include/EncoderDevice.hpp"
#include "../include/TimedPublisher.hpp"
#include "../../Common/include/Device.hpp"
#include "../../Common/include/DebugDevice.hpp"
#include "../../Common/include/Defines.hpp"
#include "../../Common/include/Capabilities.hpp"
#include "../include/config.hpp"

#include <WiFi.h>

using namespace genauto;

constexpr uint8_t TEST_DEVICE_V1_SIZE = 2;

Router genauto::CapabilitiesList::router;

Capability testDeviceV1Caps[] = {
    Capability(Button, ConstantIds::Esp::NEW_IDS_START),
    Capability(Stepper, ConstantIds::Esp::NEW_IDS_START + 1),
    Capability(Button, ConstantIds::Esp::NEW_IDS_START + 2)
};

// Capability testDeviceV1Caps[] = {
//     Capability(Button, ConstantIds::Esp::NEW_IDS_START),
//     Capability(Button, ConstantIds::Esp::NEW_IDS_START + 1),
//     Capability(Button, ConstantIds::Esp::NEW_IDS_START + 2),
//     Capability(Pwm, ConstantIds::Esp::NEW_IDS_START + 3),
//     Capability(Pwm, ConstantIds::Esp::NEW_IDS_START + 4),
//     Capability(Stepper, ConstantIds::Esp::NEW_IDS_START + 5),
//     Capability(Stepper, ConstantIds::Esp::NEW_IDS_START + 6),
//     Capability(Stepper, ConstantIds::Esp::NEW_IDS_START + 7),
//     Capability(Encoder, ConstantIds::Esp::NEW_IDS_START + 8),
//     Capability(Encoder, ConstantIds::Esp::NEW_IDS_START + 9),
//     Capability(Analog, ConstantIds::Esp::NEW_IDS_START + 10),
//     Capability(Analog, ConstantIds::Esp::NEW_IDS_START + 11),
//     Capability(Switch, ConstantIds::Esp::NEW_IDS_START + 12),
//     Capability(Switch, ConstantIds::Esp::NEW_IDS_START + 13)
// };

CapabilitiesMessage*
CapabilitiesList::capabilitiesList = nullptr;

static ButtonDeviceInst<34> button1(ConstantIds::Esp::NEW_IDS_START);
static ButtonDeviceInst<35> button2(ConstantIds::Esp::NEW_IDS_START + 1);

static PwmDevice pwm1(21, 0, ConstantIds::Esp::NEW_IDS_START + 3);
static PwmDevice pwm2(18, 0, ConstantIds::Esp::NEW_IDS_START + 4);

static StepperDevice stepper1(32, 33,  ConstantIds::Esp::NEW_IDS_START + 5);
static StepperDevice stepper2(26, 27,  ConstantIds::Esp::NEW_IDS_START + 6);
static StepperDevice stepper3(23, 25,  ConstantIds::Esp::NEW_IDS_START + 7);

static EncoderDevice encoder1(4, 5, ConstantIds::Esp::NEW_IDS_START + 8);
static EncoderDevice encoder2(36, 39, ConstantIds::Esp::NEW_IDS_START + 9);

static AnalogDevice analog1(14, ConstantIds::Esp::NEW_IDS_START + 10);
static AnalogDevice analog2(15, ConstantIds::Esp::NEW_IDS_START + 11);

static SwitchDevice switch1(MAINS_SW, ConstantIds::Esp::NEW_IDS_START + 12);
static SwitchDevice switch2(PW_SW14, ConstantIds::Esp::NEW_IDS_START + 13);
static SwitchDevice switch3(PW_SW15, ConstantIds::Esp::NEW_IDS_START + 14);
static SwitchDevice switch4(SW16, ConstantIds::Esp::NEW_IDS_START + 15);
static SwitchDevice switch5(SW17, ConstantIds::Esp::NEW_IDS_START + 16);
static SwitchDevice switch6(SW18, ConstantIds::Esp::NEW_IDS_START + 17);
static SwitchDevice switch7(SW19, ConstantIds::Esp::NEW_IDS_START + 18);
static SwitchDevice switch8(LED_SW, ConstantIds::Esp::NEW_IDS_START + 19);



static TimedPublisher timed(1000, MessageId(0, ConstantIds::Esp::NEW_IDS_START + 14));

static DebugDevice d1(99);
static DebugDevice d2(99);
static DebugDevice d3(99);

Device* devices[] = {
    (Device*)&d1,
    (Device*)&d2,
    (Device*)&d3
};

// Device* devices[] = {
//     (Device*)&stepper1,
//     (Device*)&stepper2,
//     (Device*)&stepper3,
//     (Device*)&pwm1,
//     (Device*)&pwm2,
//     (Device*)&switch1,
//     (Device*)&switch2,
//     (Device*)&deb
// };

Subscriber* subscribers[] = {
    (Subscriber*)&d1,
    (Subscriber*)&d2,
    (Subscriber*)&d3
};

Publisher* publishers[] = {
    (Publisher*)&d1,
    (Publisher*)&d2,
    (Publisher*)&d3
};

// Subscriber* subscribers[] = {
//     (Subscriber*)&stepper1,
//     (Subscriber*)&stepper2,
//     (Subscriber*)&stepper3,
//     (Subscriber*)&pwm1,
//     (Subscriber*)&pwm2,
//     (Subscriber*)&switch1,
//     (Subscriber*)&switch2
// };

// Publisher* publishers[] = {
//     (Publisher*)&button1,
//     (Publisher*)&button2,
//     (Publisher*)&button3,
//     (Publisher*)&encoder1,
//     (Publisher*)&encoder2,
//     (Publisher*)&analog1,
//     (Publisher*)&analog2,
//     (Publisher*)&timed
// };

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
    const auto& subs = subscriberList.getList();
    const auto& devs = deviceList.getList();
    const auto& pubs = publisherList.getList();

    for (int i = 0; i < deviceList.getSize(); i++) {
        Subscriber* sub = deviceList[i]->sub();
        if (sub) {
            auto id = MessageId(deviceId, devs[i]->minorId);
            router.subscribe(sub, id.to());
        }
    }
}
