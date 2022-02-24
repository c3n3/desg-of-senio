#ifndef __GENAUTO_HEX_STRING_SERIALIZER_HPP__
#define __GENAUTO_HEX_STRING_SERIALIZER_HPP__

#include "MessageSerializer.hpp"
#include "Message.hpp"
#include <stdint.h>

namespace genauto {
    class HexStringSerializer {

        // Buffer to be transmitted
        char* buffer_;
        uint16_t maxSize_; 
        uint16_t bufferIdx_;
        uint16_t currentSize_;

    public:
        /**
         * @brief Construct a new Hex String Serializer object
         */
        HexStringSerializer(int maxSize);

        ~HexStringSerializer();

        /**
         * @brief A Result enum
         */
        enum Result {
            Success = 0,
            Failure,
            IncompleteData
        };

        /**
         * @brief take a message and convert into serial representation
         *
         * @param msg the message
         */
        Result serialize(Message* msg);

        /**
         * @brief parse incoming data into the buffer properly
         *
         * @param incoming 
         * @param size 
         * @return Result 
         */
        Result parse(const uint8_t* incoming, size_t size);

        /**
         * @brief Clears any internal buffer if a message has partially been
         * received.
         */
        void cancelParse();

        /**
         * @brief Copy the internal message.
         *
         * @param msg the message
         */
        Result deserialize(Message* msg);

        /**
         * @brief Validates that a message is a valid uncorrupted message
         *
         * @param buf the buffer to check against
         * @return true 
         * @return false 
         */
        Result validate(const uint8_t* buf, size_t size);

        /**
         * @brief Gets a pointer to the buffer
         *
         * @return const uint8_t*
         */
        const char* getBuffer();

        /**
         * @brief Get the buffer size
         *
         * @return constexpr size_t
         */
        size_t maxSize();

        /**
         * @brief Get the buffer size
         *
         * @return constexpr size_t
         */
        size_t currentSize();
    };
}


#endif
