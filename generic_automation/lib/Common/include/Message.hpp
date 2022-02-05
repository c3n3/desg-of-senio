#ifndef __GENAUTO_MESSAGE_HPP__
#define __GENAUTO_MESSAGE_HPP__

#include "MessageId.hpp"
#include "StringBuilder.hpp"
#include "../include/Log.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef uint16_t location_t;


using namespace genauto;

namespace genauto {

    typedef uint16_t msgType_t;

    #define MSG_TYPE(A, B) (((uint16_t)(A)) << 8) | ((uint16_t)(B))

    

    #define NEXT(previous) \
        (((uint8_t*)previous) + sizeof(*previous))


    #define BUFFER_VAR(name, type, previous) \
        static constexpr uint16_t name ## loc_ = previous ## loc_ + sizeof(previous()); \
        inline type& name () \
        { \
            return *(type*)(buffer_ + name ## loc_); \
        }

    class Message {
    protected:
        uint8_t* buffer_;
        static const uint16_t size_loc_ = 0;
        uint16_t& size_ ()
        {
            return *(uint16_t*)(buffer_ + size_loc_);
        }

        BUFFER_VAR(id_, MessageId, size_);

        BUFFER_VAR(type_, msgType_t, msgId_);

        static constexpr uint16_t baseSize = sizeof(size_()) + sizeof(msgId_()) + sizeof(type_());

        bool alloc;

    public:
        Message(uint8_t* buffer = nullptr, uint16_t size=baseSize);

        virtual ~Message();

        MessageId& id();

        uint16_t& type();

        uint8_t* getBuffer();

        uint16_t getSize();

        void setBuffer(uint8_t* buffer);

        void toString(StringBuilder& sb);
    };
}

#endif
