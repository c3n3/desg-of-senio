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
        typedef uint32_t checksum_t;
        typedef uint32_t magic_t;
        typedef uint32_t length_t;

        // Magic number that all buffers start with
        static constexpr magic_t MAGIC = 0x12345678;

        // Buffer to be transmitted
        uint8_t buffer_[
            sizeof(magic_t) + sizeof(length_t)
            + sizeof(MSG) + sizeof(checksum_t)
        ];

        // Checksum at the end
        checksum_t* const checksum_
            = (checksum_t*)&buffer_[sizeof(buffer_) - sizeof(checksum_t)];

        // Magic number to start
        magic_t* const magic_ = (magic_t*)buffer_;

        // MsgId after magic
        Message::msgid_t* const msgId_
            = (Message::msgid_t*)&buffer_[sizeof(magic_t)];

        // Length after magic number and id
        length_t* const length_
            = (length_t*)&buffer_[sizeof(magic_t) + sizeof(Message::msgid_t)];

        // The start of actual data
        uint8_t* const dataStart_
            = &buffer_[sizeof(magic_t) + sizeof(length_t)];
        
        /**
         * @brief Used to parse data
         */
        uint8_t* parsingPtr_ = buffer_;
    public:
        /**
         * @brief Construct a new Message Serializer object
         */
        MessageSerializer()
        {
            *magic_ = MAGIC;
            *length_ = sizeof(buffer_);
        }

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
            std::memcpy(dataStart_, (void*)&msg, sizeof(msg));
            *msgId_ = msg.getMsgId();
            *checksum_ = 0;
            for (int i = 0; i < sizeof(buffer_) - sizeof(checksum_t); i++) {
                *checksum_ += buffer_[i];
            }
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
            int i = 0;
            // parse magic
            if ((void*)parsingPtr_ < (void*)magic_ + sizeof(magic_t)) {
                for (; i < size; i++) {
                    int difference = ((uint8_t*)parsingPtr_) - ((uint8_t*)magic_);
                    // Check each byte comming in for correctness
                    LOG("Difference = %u\n", difference);
                    LOG("Checking 0x%x vs 0x%x\n", *incoming, (MAGIC & 0x000000ff << difference*8) >> difference*8);
                    if (*incoming == ((MAGIC & 0x000000ff << difference*8) >> difference*8)) {
                        *parsingPtr_ = incoming[i];
                        parsingPtr_++;
                    } else if ((void*)parsingPtr_ == (void*)magic_ + sizeof(magic_t)) {
                        LOG("Success\n");
                        break;
                    }
                    else {
                        parsingPtr_ = (uint8_t*)magic_;
                    }
                    incoming++;
                }
            }
            if (i >= size) {
                LOG("Failure\n");
                return IncompleteData;
            }

            // parse msgid
            if ((void*)parsingPtr_ < (void*)msgId_ + sizeof(Message::msgid_t)) {
                for (; i < size; i++) {
                    *parsingPtr_ = incoming[i];
                    parsingPtr_++;
                    incoming++;
                    if ((void*)parsingPtr_ == (void*)msgId_ + sizeof(Message::msgid_t)) {
                        LOG("Success\n");
                        break;
                    }
                }
            }
            if (i >= size) {
                LOG("Failure\n");
                return IncompleteData;
            }

            // parse length
            if ((void*)parsingPtr_ < (void*)length_ + sizeof(length_t)) {
                for (; i < size; i++) {
                    *parsingPtr_ = incoming[i];
                    parsingPtr_++;
                    incoming++;
                    if ((void*)parsingPtr_ == (void*)length_ + sizeof(length_t)) {
                        LOG("Success\n");
                        break;
                    }
                }
            }
            if (i >= size) {
                LOG("Failure\n");
                return IncompleteData;
            }

            // We have length, parse until we have the length
            if ((void*)parsingPtr_ < (void*)buffer_ + *length_) {
                for (; i < size; i++) {
                    *parsingPtr_ = incoming[i];
                    parsingPtr_++;
                    incoming++;
                }
            }
            if ((void*)parsingPtr_ >= (void*)buffer_ + *length_) {
                return validate(buffer_, *length_);
            } else if (i >= size) {
                LOG("Failure\n");
                return IncompleteData;
            }
            LOG("Failure\n");
            return Failure;
        }

        void cancelParse()
        {
            parsingPtr_ = buffer_;
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
        Result validate(const uint8_t* buf, size_t size)
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
