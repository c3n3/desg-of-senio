#ifndef __GENAUTO_MESSAGE_HPP__
#define __GENAUTO_MESSAGE_HPP__

#include "MessageId.hpp"
#include "MessageTypeRegistry.hpp"
#include "../include/Log.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


using namespace genauto;

namespace genauto {
    typedef uint16_t msgType_t;
    typedef uint16_t msgSize_t;
    typedef uint16_t location_t;
    typedef uint8_t msgBuf_t;

    #define MESSAGE_ID_UNIQUE(class) static genauto::MessageTypeRegistry<class::classMsgType> r

    class Message {
    protected:
        uint8_t* buffer_;
        uint16_t bufferSize_;
        template<typename T>
        T& get(location_t location)
        {
            if (location > bufferSize_) {
                elog("Buffer size exceeded. Invalid results will occur.\n");
            }
            return *(T*)(buffer_ + location);
        }

        static constexpr location_t size_loc = 0;
        static constexpr location_t id_loc = size_loc + sizeof(msgSize_t);
        static constexpr location_t type_loc = id_loc + sizeof(MessageId);
        static constexpr location_t derivedStart_loc = type_loc + sizeof(msgType_t);

        msgSize_t& size_();

        static constexpr uint16_t baseSize = sizeof(uint16_t) + sizeof(MessageId) + sizeof(msgType_t);

        bool alloc;

    public:

        msgSize_t size();

        MessageId& id();

        msgType_t& type();

        Message(msgBuf_t* buffer, uint16_t bufferSize);

        Message(uint16_t size=baseSize);

        virtual ~Message();

        uint8_t* getBuffer() const;

        uint16_t getBufferSize();

        void setBuffer(uint8_t* buffer);

        virtual void log();

        Message (const Message& other);

        uint16_t getSizeSafe();
    };
}

#endif
