#include "../include/Device.hpp"
#include "../include/Message.hpp"
#include <stdint.h>

using namespace genauto;

major_t genauto::deviceId = 0;

genauto::Device::Device(minor_t minorId)
    : minorId(minorId)
{

}
