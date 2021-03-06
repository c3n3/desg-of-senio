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

    constexpr const char* deviceTypeToString(DeviceType t)
    {
    #define CASE(v) t == v ? #v :
    return CASE(Pwm)
        CASE(Stepper)
        CASE(Switch)
        CASE(Button)
        CASE(Encoder)
        CASE(Analog) "";
    #undef CASE
}

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
        const location_t IP_LOC = MAC_LOC + MAC_STR_LEN;
        const location_t CAPABILITIES_LOC = IP_LOC + sizeof(uint32_t);
    public:
        CapabilitiesMessage(Capability* list, uint16_t count);
        CapabilitiesMessage(msgBuf_t* buffer, uint16_t bufferSize);
        uint16_t& count();
        char* mac();
        uint32_t& ip();
        Capability* capablities();
        static constexpr msgType_t classMsgType = 0x0007;

        void log();
    };
}

#endif
