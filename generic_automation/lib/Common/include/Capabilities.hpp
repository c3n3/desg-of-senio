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
        Encoder
    };

    class Capability {
    public:
        DeviceType type;
        const minor_t id;
        Capability(DeviceType t, minor_t id);
    };

    template<int N>
    class Capablities : public Message {
    public:
        Capability arr[N];
        Capablities(Capability* input)
        {
            memcpy(arr, input, N);
        }
    };

    extern Capablities<2> TestDevice_V1;
}

#endif
