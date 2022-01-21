#ifndef __GENERIC_AUTOMATION_MESSAGE_SERIALIZER_HPP__
#define __GENERIC_AUTOMATION_MESSAGE_SERIALIZER_HPP__

#include "Message.hpp"
#include "Debug.hpp"

#include <stdint.h>
#include <cstring>
#include <iostream>
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
        virtual Result serialize(MSG& msg) = 0;

        /**
         * @brief parse incoming data into the buffer properly
         *
         * @param incoming 
         * @param size 
         * @return Result 
         */
        virtual Result parse(const uint8_t* incoming, size_t size) = 0;

        /**
         * @brief Clears any internal buffer if a message has partially been
         * received.
         */
        virtual void cancelParse() = 0;

        /**
         * @brief Copy the internal message.
         *
         * @param msg the message
         */
        virtual Result deserialize(MSG& msg) = 0;

        /**
         * @brief Validates that a message is a valid uncorrupted message
         *
         * @param buf the buffer to check against
         * @return true 
         * @return false 
         */
        virtual Result validate(const uint8_t* buf, size_t size) = 0;

        /**
         * @brief Gets a pointer to the buffer
         *
         * @return const uint8_t*
         */
        virtual const uint8_t* getBuffer() = 0;

        virtual bool isMsgType(const uint8_t* buf, size_t size)
        {
            return false;
        }

        /**
         * @brief Get the buffer size
         *
         * @return constexpr size_t
         */
        virtual constexpr size_t getSize();
    };
}

#endif
