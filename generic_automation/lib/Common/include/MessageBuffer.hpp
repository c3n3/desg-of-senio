#include "MessageId.hpp"
#include <stdlib.h>

using namespace genauto;
namespace genauto {

    class BaseMessage {
    public:
        virtual MessageId getId() = 0;
        virtual uint16_t getSize() = 0;
        virtual uint16_t getType() = 0;
        virtual uint8_t* getBuffer() = 0;
    };


    template<uint16_t N>
    class MessageBuffer : public BaseMessage {
        uint8_t buffer_[N];
        static const uint16_t size_location = 0;
        static const uint16_t msgId_location = sizeof(N);
        static const uint16_t type_location = (sizeof(N) + sizeof(MessageId));
    public:
        MessageBuffer(MessageId id, uint16_t type)
        {
            set(size_location, N);
            set(msgId_location, id);
            set(type_location, type);
        }

        template<typename T>
        void set(uint16_t location, T value)
        {
            memcpy(&buffer_[location], &value, sizeof(T));
        }

        template<typename T>
        T& get(uint16_t location)
        {
            return *((T*)&buffer_[location]);
        }

        uint16_t getSize()
        {
            return get<uint16_t>(size_location);
        }

        MessageId getId()
        {
            return get<MessageId>(msgId_location);
        }

        uint8_t* getBuffer()
        {
            return buffer_;
        }

        uint16_t getType()
        {
            return get<uint16_t>(type_location);
        }
    };

}

typedef MessageBuffer<16> Message16_t;
