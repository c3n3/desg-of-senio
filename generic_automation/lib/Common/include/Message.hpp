#ifndef __GENAUTO_MESSAGE_HPP__
#define __GENAUTO_MESSAGE_HPP__

#include "MessageId.hpp"
#include "StringBuilder.hpp"
#include "../include/Log.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utility>
#include <type_traits>



using namespace genauto;

namespace genauto {
    typedef uint16_t msgType_t;
    typedef uint16_t msgSize_t;
    typedef uint16_t location_t;

    #define MSG_TYPE(A, B) (((uint16_t)(A)) << 8) | ((uint16_t)(B))

    class Message {
    protected:
        uint8_t* buffer_;
        
        template<typename T>
        T& get(location_t location)
        {
            return *(T*)(buffer_ + location);
        }

        static constexpr location_t size_loc = 0;
        static constexpr location_t id_loc = size_loc + sizeof(msgSize_t);
        static constexpr location_t type_loc = id_loc + sizeof(MessageId);
        static constexpr location_t dirivedStart_loc = type_loc + sizeof(msgType_t);

        msgSize_t& size_();

        static constexpr uint16_t baseSize = sizeof(uint16_t) + sizeof(MessageId) + sizeof(msgType_t);

        bool alloc;

    public:

        msgSize_t size();

        MessageId& id();

        msgType_t& type();

        Message(uint8_t* buffer = nullptr, uint16_t size=baseSize);

        virtual ~Message();

        uint8_t* getBuffer() const;

        uint16_t getSize();

        void setBuffer(uint8_t* buffer);

        virtual void toString(StringBuilder& sb);

        template<typename MSG_T>
        operator MSG_T()
        {
            return MSG_T(getBuffer());
        }

        void log();

        Message (const Message& other);
    };
}

#endif
