#include "../include/Capabilities.hpp"

#ifdef ESP32
#include <WiFi.h>
#include "lwip/inet.h"
#endif

using namespace genauto;

MESSAGE_ID_UNIQUE(CapabilitiesMessage);

Capability::Capability(DeviceType t, minor_t id)
    : id(id), type(t)
{}

CapabilitiesMessage::CapabilitiesMessage(Capability* list, uint16_t countIn)
    : Message(countIn * sizeof(Capability) + Message::baseSize + sizeof(uint16_t) + MAC_STR_LEN)
{
    dlog("Count: %d\n", countIn);
#ifdef ESP32
    // If on esp32, we setup the mac
    String temp = WiFi.macAddress();
    for (int i = 0; i < MAC_STR_LEN; i++) {
        mac()[i] = temp[i];
    }
    mac()[MAC_STR_LEN - 1] = '\0';
#endif
    memcpy(capablities(), list, countIn*sizeof(Capability));
    count() = countIn;
    type() = CapabilitiesMessage::classMsgType;
    log();
}

CapabilitiesMessage::CapabilitiesMessage(msgBuf_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{}

char* CapabilitiesMessage::mac()
{
    return &get<char>(MAC_LOC);
}

uint32_t& CapabilitiesMessage::ip()
{
    return get<uint32_t>(IP_LOC);
}

Capability* CapabilitiesMessage::capablities()
{
    return &get<Capability>(CAPABILITIES_LOC);
}

uint16_t& CapabilitiesMessage::count()
{
    return get<uint16_t>(COUNT_LOC);
}

void CapabilitiesMessage::log()
{
    _printf("Capabilities message = [count: %d] [size: %d] [mac: %s] [ip: %u]", count(), size(), mac(), ip());
    for (int i = 0 ; i < count(); i++) {
        _printf("{cap=%d,id=%d}", capablities()[i].type, capablities()[i].id);
    }
    _printf("\n");
}

