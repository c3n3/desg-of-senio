/*

  StringBuilder.cpp - Simple string builder

  Created by Caden Churchman, December 15, 2021.

*/

#include "StringBuilder.hpp"
#include <iostream>


using namespace genauto;

StringBuilder::StringBuilder(uint32_t bufferSize)
    : buffer_(new char[bufferSize]), size_(bufferSize), index_(0)
{}

StringBuilder::~StringBuilder()
{
    delete buffer_;
}

StringBuilder::Result StringBuilder::appendString(const char* string)
{
    Result r;
    while (*string != '\0') {
        if (r = appendChar(*string)) {
            return r;
        }
        string++;
    }
    return Success;
}

StringBuilder::Result StringBuilder::appendChar(char c)
{
    if (index_ == size_ - 1) {
        return NoBufferSpace;
    }
    buffer_[index_++] = c;
    return Success;
}

StringBuilder::Result StringBuilder::appendInt(int16_t num)
{
    if (num == 0) {
        return appendChar('0');
    }

    // Max digits for a 16 bit is 5, +1 for \0
    char temp[6];
    if (num < 0) {
        appendChar('-');
    }
    temp[sizeof(temp) - 1] = '\0';
    int index = sizeof(temp) - 1;
    while (num != 0 && index >= 1) {
        index--;
        temp[index] = (num % 10) + '0';
        num = num / 10;
    }
    return appendString(&temp[index]);
}

// Very naive implementation for simplicity and speed
StringBuilder::Result StringBuilder::appendFloat(float num, uint8_t decimals)
{
    // Floor
    int32_t top = num;

    // get to form 0.XXXXX
    float temp = (num - ((float)top));
    for (;decimals --> 0;) temp = temp * 10;
    uint32_t bottom = temp;

    Result r;
    if (r = appendInt(top)) {
        return r;
    }
    if (r = appendChar('.')) {
        return r;
    }
    return appendInt(bottom);
}

void StringBuilder::clear()
{
    index_ = 0;
}

const char* StringBuilder::getString()
{
    buffer_[index_] = '\0';
    return buffer_;
}
