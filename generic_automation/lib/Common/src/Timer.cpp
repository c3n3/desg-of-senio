#include "../include/Timer.hpp"
#include "../include/Log.hpp"

#ifndef ARDUINO

msTimer_t Timer::msTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
    return duration.count() / 2000;
}

Timer::Timer(const char * name)
    : name(name)
{
    start = std::chrono::high_resolution_clock::now();
}

#else

Timer::Timer(const char* name)
    : name(name)
{
    start = millis();
}

msTimer_t Timer::msTime()
{
    return millis() - start;
}

#endif

void Timer::log()
{
    dlog("%s: %u ms\n", name,  msTime());
}
