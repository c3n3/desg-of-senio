#ifndef __GENAUTO_MESSAGE_SENDER_HPP__
#define __GENAUTO_MESSAGE_SENDER_HPP__

#include <stdint.h>

namespace genauto
{
    class MessageSender {
    public:
        virtual void send(const uint8_t* buffer, int size) = 0;
    };
}


#endif
