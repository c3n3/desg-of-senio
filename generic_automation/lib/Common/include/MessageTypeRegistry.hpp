#ifndef __GENAUTO_MESSAGE_TYPE_REGISTRY_HPP__
#define __GENAUTO_MESSAGE_TYPE_REGISTRY_HPP__

#include "Log.hpp"
#include <stdint.h>

namespace genauto {
    template<uint16_t TYPE>
    class MessageTypeRegistry {
    public:
        static uint16_t count;
        MessageTypeRegistry()
        {
            if (count > 0) {
                elog("Duplicate message type %x, aborting...\n", TYPE);
                uint8_t test = *(uint8_t*)nullptr;
            }
            count++;
        }
    };

    template<uint16_t TYPE>
    uint16_t MessageTypeRegistry<TYPE>::count = 0;
}

#endif
