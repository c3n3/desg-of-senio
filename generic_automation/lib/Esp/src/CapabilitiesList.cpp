// TODO: Make autogen

#include "../include/DeviceList.hpp"
#include "../include/ButtonDevice.hpp"
#include "../include/PwmDevice.hpp"
#include "../../Common/include/Defines.hpp"


using namespace genauto;

constexpr uint8_t TEST_DEVICE_V1_SIZE = 2;
constexpr uint8_t SUBSCRIBER_SIZE = 1;
constexpr uint8_t PUBLISHER_SIZE = 1;

static Capability testDeviceV1Caps[] = {
    Capability(Button, 10),
    Capability(Pwm, 11)
};

Capablities caps(testDeviceV1Caps, ARRSIZE(testDeviceV1Caps));

ButtonDeviceInst<22> button;
PwmDevice pwm(10, 0);

Device* devices[] = {
    (Device*)&button,
    (Device*)&pwm
};

Subscriber* subscribers[] = {
    (Subscriber*)&pwm
};

Publisher* publishers[] = {
    (Publisher*)&button
};

Capablities* genauto::DeviceList::getList()
{
    return &caps;
}


uint16_t genauto::DeviceList::getSize()
{
    return TEST_DEVICE_V1_SIZE;
}

Device** genauto::DeviceList::getDevices()
{
    return devices;
}

void genauto::DeviceList::init()
{

}
