#ifndef __GENERIC_AUTOMATION_MESSAGE_SERIALIZER_HPP__
#define __GENERIC_AUTOMATION_MESSAGE_SERIALIZER_HPP__

#include "Message.hpp"

#include <stdint.h>
#include <cstring>

namespace genauto {
    /**
     * @brief Used to serialize and deserialize messages
     * 
     * Currently the implementation simply serializes and puts into a buffer.
     * We will need to add more information in order to properly detect messages
     * when receiving and parsing data. The magic number is not a particularly
     * foolproof method, and needs to be more robust. This could
     * include some sort of zero insertions such that a magic number
     * can never be replicated in the data section of a serialization
     * 
     * TODO: Some sort of failproof length identification
     */
    template<class MSG>
    class MessageSerializer {
        typedef uint32_t checksum_t;
        typedef uint32_t magic_t;
        typedef uint32_t length_t;

        // Magic number that all buffers start with
        constexpr magic_t MAGIC = 0x12345678;

        // Buffer to be transmitted
        uint8_t buffer_[sizeof(MSG) + sizeof(checksum_t)];

        // Checksum at the end
        checksum_t* const checksum_
            = (checksum_t*)&buffer_[sizeof(buffer_) - sizeof(checksum_t)];

        // Magic number to start
        magic_t* const magic_ = (magic_t*)buffer_;

        // Length after magic number
        length_t* const length_
            = (length_t*)&buffer_[sizeof(magic_t)];

        // The start of actual data
        uint8_t* const dataStart_
            = &buffer_[sizeof(magic_t) + sizeof(length_t)];

    public:
        enum Result {
            Success,
            Failure
        };
        /**
         * @brief take a message and convert into serial representation
         *
         * @param msg the message
         */
        Result serialize(MSG& msg)
        {
            std::memcpy(dataStart_, (void*)&msg, sizeof(msg));
            *checksum_ = 0;
            for (int i = 0; i < sizeof(msg); i++) {
                *checksum_ += buffer_[i];
            }
        }

        /**
         * @brief take a message and convert into serial representation
         *
         * @param msg the message
         */
        Result deserialize(MSG& msg)
        {
            if (sizeof(msg) > sizeof(buffer_)) {
                return Failure;
            }
            std::memcpy((void*)&msg, dataStart_, sizeof(msg));
            return Success;
        }

        /**
         * @brief Validates that a message is a valid uncorrupted message
         *
         * @param buf the buffer to check against
         * @return true 
         * @return false 
         */
        Result validate(uint8_t* buf, size_t size)
        {
            if (size < sizeof(checksum_t)) {
                return Failure;
            }
            checksum_t check = 0;
            for (int i = 0; i < size - sizeof(checksum_t); i++) {
                check += buf[i];
            }
            return check == *(checksum_t*) &buf[size - sizeof(checksum_t)]
                            ? Success : Failure;
        }

        /**
         * @brief Gets a pointer to the buffer
         *
         * @return const uint8_t*
         */
        const uint8_t* getBuffer()
        {
            return buffer_;
        }

        /**
         * @brief Get the buffer size
         *
         * @return constexpr size_t
         */
        constexpr size_t getSize()
        {
            return sizeof(buffer_);
        }
    };
}

#endif
