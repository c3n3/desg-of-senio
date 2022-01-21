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
            sizeof(Message::msgid_t) + sizeof(MSG) * 2
        ];

        Message::msgid_t* const msgId_ = (Message::msgid_t*)buffer_;
        MSG* const msg_ = (MSG*)buffer_ + sizeof(Message::msgid_t);
        int bufferIdx;
    public:
        /**
         * @brief Construct a new Hex String Serializer object
         */
        HexStringSerializer(): bufferIdx(0)
        {}

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
        Result serialize(MSG& msg)
        {
            uint8_t* serial = (uint8_t*) &msg;
            int bufferIdx = sizeof(Message::msgid_t);
            // Iterate over bytes
            for (int i = 0; i < sizeof(msg); i++) {
                // Iterate over 4 bits (hex)
                for (int hexIdx = 0; hexIdx < 2; hexIdx++) {
                    uint8_t hex = (serial[i] >> (hexIdx * 4)) & 0x0F;
                    buffer_[bufferIdx++] = 'A' + hex;
                }
            }
            return Success;
        }

        /**
         * @brief parse incoming data into the buffer properly
         *
         * @param incoming 
         * @param size 
         * @return Result 
         */
        Result parse(const uint8_t* incoming, size_t size)
        {
            int byteOn = 0;
            if (size > sizeof(buffer_)) {
                return Failure;
            }
            for (int i = 0; i < size; i++) {
                uint8_t byteImplant = 0;
                byteImplant |= ((incoming[i] - 'A') << (byteOn * 4));
                if (byteImplant == 1) {
                    buffer_[bufferIdx++] = byteImplant;
                }
                byteOn = (byteOn + 1) % 2;
            }
            if (bufferIdx == sizeof(buffer_)) {
                bufferIdx = 0;
                return Success;
            } else {
                return IncompleteData;
            }
        }

        /**
         * @brief Clears any internal buffer if a message has partially been
         * received.
         */
        void cancelParse()
        {
            bufferIdx = 0;
        }

        /**
         * @brief Copy the internal message.
         *
         * @param msg the message
         */
        Result deserialize(MSG& msg)
        {
            msg = *msg_;
            return Success;
        }

        /**
         * @brief Validates that a message is a valid uncorrupted message
         *
         * @param buf the buffer to check against
         * @return true 
         * @return false 
         */
        Result validate(const uint8_t* buf, size_t size)
        {
            return Success;
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
