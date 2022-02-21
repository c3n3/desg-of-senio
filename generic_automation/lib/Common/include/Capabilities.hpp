#ifndef __GENAUTO_CAPABILITIES_IDS_HPP__
#define __GENAUTO_CAPABILITIES_IDS_HPP__

#include "List.hpp"
#include "Device.hpp"
#include "Types.hpp"
#include "Message.hpp"
#include <stdio.h>

namespace genauto {
    enum DeviceType {
        Pwm,
        Stepper,
        Switch,
        Button,
        Encoder,
        Analog
    };

    class Capability {
    public:
        DeviceType type;
        const minor_t id;
        Capability(DeviceType t, minor_t id);
    };

    class CapabilitiesMessage : public Message {
        const location_t COUNT_LOC = Message::derivedStart_loc;
        const location_t CAPABILITIES_LOC = COUNT_LOC + sizeof(uint16_t);
    public:
        CapabilitiesMessage(Capability* list = nullptr, uint16_t count = 0, msgBuf_t* buffer = nullptr);
        uint16_t count();
        Capability* capablities();
    };
}

#endif
