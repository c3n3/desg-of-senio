#ifndef __GENAUTO_MESSAGE_HPP__
#define __GENAUTO_MESSAGE_HPP__

#include "MessageId.hpp"
#include <stdlib.h>

typedef uint16_t location_t;

#define BUFFER_VAR(previous, type, name) \
type* const name = (type*)(((uint8_t*)&previous) + sizeof(type))

using namespace genauto;
namespace genauto {

    typedef uint16_t msgType_t;

    class BaseMessage {
    public:
        virtual MessageId getId() = 0;
        virtual uint16_t getSize() = 0;
        virtual msgType_t getType() = 0;
        virtual uint8_t* getBuffer() = 0;
    };


    template<uint16_t N>
    class Message : public BaseMessage {
    protected:
        uint8_t buffer_[N];
        uint16_t* const size_ = (uint16_t*)buffer_;
        BUFFER_VAR(size_, MessageId, msgId_);
        BUFFER_VAR(msgId_, msgType_t, type_);
    public:
        Message(MessageId id, uint16_t type)
        {
            set(size_location, N);
            set(msgId_location, id);
            set(type_location, type);
        }

        uint16_t getSize()
        {
            return *size_;
        }

        MessageId getId()
        {
            return *msgId_;
        }

        uint8_t* getBuffer()
        {
            return buffer_;
        }

        uint16_t getType()
        {
            return *type_;
        }

    };

}

typedef Message<16> Message16_t;


#endif
