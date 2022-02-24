#ifndef __GENAUTO_CAPABILITIES_IDS_HPP__
#define __GENAUTO_CAPABILITIES_IDS_HPP__

#include "List.hpp"
#include "Device.hpp"
#include "Types.hpp"
#include "Message.hpp"

namespace genauto {
    enum DeviceType : uint8_t {
        Pwm,
        Stepper,
        Switch,
        Button,
        Encoder,
        Analog
    };

    class __attribute__((packed)) Capability {
    public:
        DeviceType type;
        const minor_t id;
        Capability(DeviceType t, minor_t id);
    };

    class CapabilitiesMessage : public Message {
        using Message::Message;
        static constexpr uint16_t MAC_STR_LEN = 19;
        const location_t COUNT_LOC = Message::derivedStart_loc;
        const location_t MAC_LOC = COUNT_LOC + sizeof(uint16_t);
        const location_t CAPABILITIES_LOC = COUNT_LOC + MAC_STR_LEN;
    public:
        CapabilitiesMessage(Capability* list = nullptr, uint16_t count = 0, msgBuf_t* buffer = nullptr);
        uint16_t& count();
        char* mac();
        Capability* capablities();
        static constexpr msgType_t classMsgType = 0x0006;

        void log();
    };
}

#endif
