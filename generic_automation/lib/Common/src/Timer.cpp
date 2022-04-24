#include "../include/Timer.hpp"
#include "../include/Log.hpp"

#ifndef ARDUINO

msTimer_t Timer::msTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
    return duration.count() / 2000;
}

void Timer::delay(uint64_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(uint64_t(ms)));
}

Timer::Timer(const char * name)
    : name(name)
{
    start = std::chrono::high_resolution_clock::now();
}

#else

void Timer::delay(uint64_t ms)
{
    delay(ms)
}

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
