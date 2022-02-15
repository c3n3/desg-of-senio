#include "../include/Capabilities.hpp"

using namespace genauto;

Capability::Capability(DeviceType t, minor_t id)
    : id(id), type(t)
{}


#define TEST_DEVICE_V1_SIZE 2

static Capability testDeviceV1Caps[TEST_DEVICE_V1_SIZE] = {
    Capability(Pwm, 10),
    Capability(Pwm, 10)
};

Capablities<TEST_DEVICE_V1_SIZE> genauto::TestDevice_V1(testDeviceV1Caps);
