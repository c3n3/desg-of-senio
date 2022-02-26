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
         * @brief Set the 
         *
         * @param d 
         */
        void set(Direction d);

    public:
        /**
         * @brief Major number id
         */
        major_t major;

        /**
         * @brief Minor number id
         */
        minor_t minor;

        /**
         * @brief Get major
         * TODO: REMOVE
         */
        major_t getMajor();

        /**
         * @brief Set the Major
         *
         * TODO: REMOVE
         * @return major_t 
         */
        void setMajor(major_t m);

        /**
         * @brief Set the Minor
         *
         * TODO: REMOVE
         * @return major_t 
         */
        void setMinor(minor_t m);

        /**
         * @brief Get minor
         * 
         * TODO: REMOVE
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
    
    private:
        static const uint8_t DIRECTION_BIT = sizeof(MessageId::major) * 8 - 1;
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
