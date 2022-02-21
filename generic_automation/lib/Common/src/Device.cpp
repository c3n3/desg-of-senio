#include "../include/Device.hpp"
#include "../include/Message.hpp"
#include <stdint.h>

using namespace genauto;

genauto::Device::Device(minor_t minorId)
    : minorId(minorId)
{

}
