#include "TimedTask.hpp"
#include "../lib/Common/include/Log.hpp"
#include <chrono>

using namespace genauto;

TimedTask::TimedType TimedTask::strToType(std::string str)
{
    #define CHECK(x) if (str == #x) return x;
    CHECK(Periodic);
    CHECK(Daily);
    CHECK(Weekly);
    return Unknown;
    #undef CHECK
}

TimedTask::TimedTask(json j)
{
    if (j.contains("name")) {
        name = j["name"];
    } else {
        elog("No name\n");
    }
    if (j.contains("value")) {
        if (j["value"].contains("value")) {
            value = j["value"]["value"];
        } else {
            elog("No time value\n");
        }
        if (j["value"].contains("type")) {
            type = strToType(j["value"]["type"]);
        } else {
            elog("No type");
        }
        if (j["value"].contains("secondaryValue")) {
            secondaryValue = j["value"]["secondaryValue"];
        }
    } else {
        elog("No value\n");
    }
}

bool TimedTask::shouldExecute()
{
    if (!enabled_) {
        return false;
    }

    switch (type) {
        case Periodic:
            if (currentTimeMs() - startTime_ > (value*60*1000)) {
                startTime_ = currentTimeMs();
                return true;
            }
            return false;
        case Daily:
            time_t theTime = time(NULL);
            struct tm *aTime = localtime(&theTime);
            int day = aTime->tm_mday;
            int hour=aTime->tm_hour;
            int min=aTime->tm_min;
            uint64_t currentMinute = min + hour*60;
            if (currentMinute > value && startTime_ != day) {
                startTime_ = day;
                return true;
            }
            return false;
        case Weekly:
            time_t theTime = time(NULL);
            struct tm *aTime = localtime(&theTime);
            int day = aTime->tm_mday;
            int hour=aTime->tm_hour;
            int min=aTime->tm_min;
            int weekDay = aTime->tm_wday;
            uint64_t currentMinute = min + hour*60 + day*24*60;
            if (currentMinute > value && startTime_ != weekDay) {
                startTime_ = weekDay;
                return true;
            }
            return false;
    }

    return true;
}

void TimedTask::enable()
{
    enabled_ = true;
    startTime_ = currentTimeMs();
}

uint64_t TimedTask::currentTimeMs()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start_);
    return duration.count() / 2000;
}
