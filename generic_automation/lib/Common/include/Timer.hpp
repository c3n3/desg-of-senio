#ifndef __GENAUTO_TIMER_HPP__
#define __GENAUTO_TIMER_HPP__

#include "Map.hpp"

#ifndef ARDUINO
#include <chrono>
#else
#include "Arduino.h"
#endif

using namespace genauto;

namespace genauto {
    typedef unsigned long msTimer_t;
    struct Timer {
        Timer(const char* name);
        const char* name;
        msTimer_t msTime();
        void log();
#ifndef ARDUINO
    std::chrono::high_resolution_clock::time_point  start;
    std::chrono::duration<float> duration;
#else
    msTimer_t start;
#endif
    };
}

#endif
