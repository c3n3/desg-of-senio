#ifndef __GENAUTO_MESSAGE_ID_HPP__
#define __GENAUTO_MESSAGE_ID_HPP__

#include "Types.hpp"

#include <stdint.h>

namespace genauto {
    class __attribute__((packed)) MessageId {
    public:
        /**
         * @brief Specifies direction the message is going in
         */
        enum Direction {
            From = 0,
            To = 1
        };
    private:
        /**
         * @brief Major number id
         */
        major_t major_;

        /**
         * @brief Minor number id
         */
        minor_t minor_;

        /**
         * @brief Set the 
         *
         * @param d 
         */
        void set(Direction d);

        static const uint8_t DIRECTION_BIT = sizeof(MessageId::major_) * 8 - 1;
    public:
        /**
         * @brief Get major
         */
        major_t getMajor();

        /**
         * @brief Get minor
         * 
         * @return uint8_t 
         */
        minor_t getMinor();

        /**
         * @brief Sets the message to 'to'
         *
         * @return MessageId& 
         */
        MessageId& to();

        /**
         * @brief Sets the message to 'from'
         *
         * @return MessageId& 
         */
        MessageId& from();

        /**
         * @brief Get the Direction object
         *
         * @return Direction 
         */
        Direction getDirection();

        /**
         * @brief Useful for using as a map key
         * 
         * @param other 
         * @return bool 
         */
        bool operator <(const MessageId& other) const;

        /**
         * @brief Equals
         *
         * @param other 
         * @return bool
         */
        bool operator ==(const MessageId& other);

        /**
         * @brief Equals
         *
         * @param other 
         * @return bool
         */
        bool operator !=(const MessageId& other);

        /**
         * @brief Create new id
         *
         * @param major
         * @param minor
         */
        MessageId(uint16_t major, minor_t minor, Direction d = From);

        /**
         * @brief Copy new id
         *
         * @param other
         */
        MessageId(const MessageId& other);

        /**
         * @brief Default ctor
         */
        MessageId();

    };

    namespace ConstantIds {
        static const major_t MAJOR_ALL = 0;
        static const major_t SERVER_MAJOR = 1;
        static const minor_t MINOR_ALL = 0;

        // Constant server minor ids
        namespace Server {
        }

        namespace Esp {
            static const minor_t SUB_MANAGER = 1;

            // This must be the last id in the constant id list
            static const minor_t NEW_IDS_START = SUB_MANAGER + 1;
        }
    }
}

#endif
