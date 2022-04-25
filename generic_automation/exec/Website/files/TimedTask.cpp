#include "TimedTask.hpp"
#include "../lib/Common/include/Log.hpp"
#include "../lib/Common/include/Timer.hpp"
#include "../database/Database.hpp"
#include "Task.hpp"
#include "Common.h"
#include <chrono>

using namespace genauto;

void TimedLoop::init()
{
    loop = new TimedLoop();
    loop->run();
}

void TimedLoop::addTask(std::string name, TimedTask* newTask)
{
    dlog("Here\n");
    auto t = std::make_pair(name, newTask);
    dlog("Here\n");
    tasks.insert(t);
}

void TimedLoop::removeTask(std::string name)
{
    auto res = tasks.find(name);
    if (res != tasks.end()) {
        tasks.erase(res);
    }
}

bool TimedLoop::contains(std::string name)
{
    return tasks.count(name);
}

void TimedLoop::updateTask(json& j)
{
    if (j.contains("name")) {
        if (contains(j["name"])) {
            tasks[j["name"]]->updateJson(j);
        } else {
            removeTask(j["name"]);
            dlog("Removing invalid task\n");
        }
    } else {
        elog("No name\n");
    }
}

bool TimedLoop::exec()
{
    for (auto& kv : tasks) {
        if (kv.second->shouldExecute()) {
            json task = find(kv.second->task, JsonFile::tasks.j);
            if (task.is_null()) {
                elog("Invalid timed event\n");
                continue;
            }
            Task* t = new Task(task["value"]);
            t->run();
        }
    }
    Timer::delay(5000);
    return true;
}

TimedLoop::TimedLoop()
{
    dlog("Init timed loop\n");
    for (auto& el : JsonFile::timedEvents.j.items()) {
        dlog("Adding event %s\n", el.value()["name"].get<std::string>().c_str());
        addTask(el.value()["name"], new TimedTask(el.value()));
    }
    run();
}

TimedTask::TimedType TimedTask::strToType(std::string str)
{
    #define CHECK(x) if (str == #x) return x;
    CHECK(Periodic);
    CHECK(Daily);
    CHECK(Weekly);
    return Unknown;
    #undef CHECK
}

void TimedTask::updateJson(json& j)
{
    if (j.contains("name")) {
        name = j["name"];
    } else {
        elog("No name\n");
    } if (j.contains("minutes")) {
        minutes = j["minutes"];
    } else {
        elog("No time value\n");
    } if (j.contains("type")) {
        type = strToType(j["type"]);
    } else {
        elog("No type");
    } if (j.contains("hours")) {
        hours = j["hours"];
    } else {
        elog("No hours");
    } if (j.contains("days")) {
        days = j["days"];
    } else {
        elog("No hours");
    } if (j.contains("enabled")) {
        enabled_ = j["enabled"];
    } else {
        elog("No hours");
    }
}

TimedTask::TimedTask(json& j)
    : startTime_(1000), enabled_(false)
{
    updateJson(j);
}

bool TimedTask::shouldExecute()
{
    if (!enabled_) {
        return false;
    }
    switch (type) {
        case Periodic: {
            if (currentTimeMs() - startTime_ > (minutes*60*1000 + hours*60*60*1000)) {
                startTime_ = currentTimeMs();
                return true;
            }
            return false;
        }
        case Daily: {
            time_t theTime = time(NULL);
            struct tm *aTime = localtime(&theTime);
            int day = aTime->tm_mday;
            int hour=aTime->tm_hour;
            int min=aTime->tm_min;
            uint64_t currentMinute = min + hour*60;
            if (currentMinute > (hours*60*60 + minutes) && startTime_ != day) {
                startTime_ = day;
                return true;
            }
            return false;
        }
        case Weekly: {
            time_t theTime = time(NULL);
            struct tm *aTime = localtime(&theTime);
            int day = aTime->tm_mday;
            int hour=aTime->tm_hour;
            int min=aTime->tm_min;
            int weekDay = aTime->tm_wday;
            uint64_t currentMinute = min + hour*60 + day*24*60;
            if (currentMinute > (hours*60*60 + minutes + days*24*60) && startTime_ != weekDay) {
                startTime_ = weekDay;
                return true;
            }
            return false;
        }
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

TimedLoop* TimedLoop::loop;

std::unordered_map<std::string, TimedTask*> TimedLoop::tasks;
