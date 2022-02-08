#ifndef __GENAUTO_MESSAGE_ID_HPP__
#define __GENAUTO_MESSAGE_ID_HPP__

#include <stdint.h>
#include "StringBuilder.hpp"

namespace genauto {
    class __attribute__((packed)) MessageId {

        /**
         * @brief Major number id
         */
        uint16_t major_;

        /**
         * @brief Minor number id
         */
        uint8_t minor_;

        static const DIRECTION_BIT = sizeof(MessageId::major_) * 8 - 1;
    public:
        /**
         * @brief Specifies direction the message is going in
         */
        enum Direction {
            From = 0,
            To = 1
        };

        /**
         * @brief Get major
         */
        uint16_t getMajorId();

        /**
         * @brief Get minor
         * 
         * @return uint8_t 
         */
        uint8_t getMinor();

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
        bool operator <(const MessageId& other);

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
        MessageId(uint16_t major, uint8_t minor, Direction d = From);

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

        /**
         * @brief Makes a string from the id
         *
         * @param sb the builder to create string from
         */
        void toString(StringBuilder& sb) const;
    };
}

#endif
