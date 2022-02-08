#ifndef __GENAUTO_MESSAGE_ID_HPP__
#define __GENAUTO_MESSAGE_ID_HPP__

#include <stdint.h>
#include "StringBuilder.hpp"

namespace genauto {
    struct __attribute__((packed)) MessageId {
        /**
         * @brief Major number id
         */
        uint16_t major;

        /**
         * @brief Minor number id
         */
        uint8_t minor;

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
        MessageId(uint16_t major, uint8_t minor);

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
