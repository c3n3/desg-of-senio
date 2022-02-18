#include "../include/Capabilities.hpp"

using namespace genauto;

Capability::Capability(DeviceType t, minor_t id)
    : id(id), type(t)
{}


CapabilitiesMessage::CapabilitiesMessage(Capability* list, uint16_t count, msgBuf_t* buffer)
    : Message(buffer, count * sizeof(Capability) + Message::baseSize)
{
    if (list != nullptr) {
        memcpy(capablities(), list, count*sizeof(Capability));
    }
}

Capability* CapabilitiesMessage::capablities()
{
    return get<Capability*>(CAPABILITIES_LOC);
}

uint16_t CapabilitiesMessage::count()
{
    return get<uint16_t>(COUNT_LOC);
}

