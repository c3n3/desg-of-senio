#ifndef __GENAUTO_HEX_STRING_SERIALIZER_HPP__
#define __GENAUTO_HEX_STRING_SERIALIZER_HPP__

#include "MessageSerializer.hpp"
#include "Message.hpp"
#include "Debug.hpp"
#include <stdint.h>
#include <cstring>
#include <iostream>
namespace genauto {
    template<class MSG>
    class HexStringSerializer {
        
        // Buffer to be transmitted
        uint8_t buffer_[
            sizeof(magic_t) + sizeof(length_t)
            + sizeof(MSG) + sizeof(checksum_t)
        ];
    public:
        /**
         * @brief A Result enum
         */
        enum Result {
            Success,
            Failure,
            IncompleteData
        };

        /**
         * @brief take a message and convert into serial representation
         *
         * @param msg the message
         */
        Result serialize(MSG& msg) = 0;

        /**
         * @brief parse incoming data into the buffer properly
         *
         * @param incoming 
         * @param size 
         * @return Result 
         */
        Result parse(const uint8_t* incoming, size_t size) = 0;

        /**
         * @brief Clears any internal buffer if a message has partially been
         * received.
         */
        void cancelParse() = 0;

        /**
         * @brief Copy the internal message.
         *
         * @param msg the message
         */
        Result deserialize(MSG& msg) = 0;

        /**
         * @brief Validates that a message is a valid uncorrupted message
         *
         * @param buf the buffer to check against
         * @return true 
         * @return false 
         */
        Result validate(const uint8_t* buf, size_t size) = 0;

        /**
         * @brief Gets a pointer to the buffer
         *
         * @return const uint8_t*
         */
        const uint8_t* getBuffer() = 0;

        /**
         * @brief Get the buffer size
         *
         * @return constexpr size_t
         */
        constexpr size_t getSize();
    };
}


#endif
