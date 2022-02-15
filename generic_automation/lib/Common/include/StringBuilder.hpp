#ifndef __GENERIC_AUTOMATION_STRING_BUILDER_HPP__
#define __GENERIC_AUTOMATION_STRING_BUILDER_HPP__

#include <stdint.h>

namespace genauto {
    class StringBuilder {
        int index_;
        char* buffer_;
        uint32_t size_;
    public:
        /**
         * @brief Used to communicate what the result of a function is
         * 
         */
        enum Result {
            Success = 0,
            Failure,
            NoBufferSpace
        };

        /**
         * @brief Creates a buffer of the given size
         *
         * @param bufferSize The given size
         */
        StringBuilder(uint32_t bufferSize);

        /**
         * @brief Cleans up the buffer
         */
        ~StringBuilder();

        /**
         * @brief Appends a string to the system
         */
        Result appendString(const char*);

        /**
         * @brief Appends char
         *
         * @return Result
         */
        Result appendChar(char);

        /**
         * @brief Appends an integer to the string
         *
         * @param num The number to add
         */
        Result appendInt(int32_t num);

        /**
         * @brief Appends a float to the string
         *
         * @param num The float to add
         * @param decimals The amount of decimals to place
         */
        Result appendFloat(float num, uint8_t decimals = 2);

        /**
         * @brief Clears the string builder so you can make a new string
         */
        void clear();

        /**
         * @brief Returns a pointer to the start of the internal buffer.
         * Do not use this once the string builder has been destroyed
         *
         * @return const char*
         */
        const char* getString();
    };
}

#endif
