#ifndef __GENERIC_AUTOMATION_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_MESSAGE_HPP__

#include <stdint.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class Message {
    protected:
        const uint16_t msgId;
    };
}

#endif
