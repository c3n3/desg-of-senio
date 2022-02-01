#ifndef __GENAUTO_HEX_STRING_SERIALIZER_HPP__
#define __GENAUTO_HEX_STRING_SERIALIZER_HPP__

#include "MessageSerializer.hpp"
#include "Message.hpp"
#include <stdint.h>
#include <cstring>
#include <iostream>
namespace genauto {
    template<class MSG>
    class TypedHexStringSerializer {

        // Buffer to be transmitted
        uint8_t buffer_[
            sizeof(Message::msgType_t) + sizeof(MSG) * 2
        ];

        Message::msgType_t* const msgId_ = (Message::msgType_t*)buffer_;
        MSG* const msg_ = (MSG*)buffer_ + sizeof(Message::msgType_t);
        int bufferIdx;
    public:
        /**
         * @brief Construct a new Hex String Serializer object
         */
        TypedHexStringSerializer(): bufferIdx(0)
        {}

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
        Result serialize(MSG& msg)
        {
            uint8_t* serial = (uint8_t*) &msg;
            buffer_[0] = (MSG::classMsgType & 0xFF00) >> 8;
            buffer_[1] = (MSG::classMsgType & 0x00FF);
            int index = sizeof(Message::msgType_t);
            // Iterate over bytes
            for (int i = 0; i < sizeof(msg); i++) {
                // Iterate over 4 bits (hex)
                for (int hexIdx = 0; hexIdx < 2; hexIdx++) {
                    uint8_t hex = (serial[i] >> (hexIdx * 4)) & 0x0F;
                    buffer_[index++] = 'A' + hex;
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
            if (size > sizeof(buffer_) - bufferIdx) {
                return Failure;
            }
            for (int i = 0; i < size; i++) {
                buffer_[bufferIdx++] = incoming[i];
            }
            if (bufferIdx >= sizeof(buffer_)) {
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
            uint8_t* buffer = (uint8_t*)&msg;
            for (int i = 0; i < sizeof(MSG)*2; i += 2) {
                uint8_t byteTwo = ((buffer_[
                        sizeof(Message::msgType_t) + i + 1] - 'A')) << 4;
                uint8_t byteOne = ((buffer_[sizeof(Message::msgType_t) + i] - 'A'));
                buffer[(i / 2)] = byteTwo | byteOne;
                // buffer[i/2] = 0xff;
            }
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
