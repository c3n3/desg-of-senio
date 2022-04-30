#include "TimedTask.hpp"
#include "DeviceSubscribeManager.hpp"
#include "../lib/Common/include/Log.hpp"
#include "../lib/Common/include/Timer.hpp"
#include "../lib/Common/include/ButtonMessage.hpp"
#include "../database/Database.hpp"
#include "Task.hpp"
#include "Common.h"
#include <chrono>

using namespace genauto;

std::unordered_map<std::string, EventTask> EventTask::events;


EventTask::EventTask(std::string task)
    : name(task),
    Device(0), // We don't care about this id
    Subscriber()
{}

EventTask::EventTask()
    : name(""),
    Device(0), // We don't care about this id
    Subscriber()
{}

void EventTask::execute()
{
    Message* msg = nextMessage();
    if (msg->type() == ButtonMessage::classMsgType) {
        json task = find(name, JsonFile::tasks.j);
        dlog("Running task '%s'\n", name.c_str());
        if (task.is_null()) {
            elog("Invalid timed event\n");
            return;
        }
        Task* t = new Task(task["value"], task["name"]);
        t->run();
    }
}

void EventTask::add(std::string name, MessageId from)
{
    if (!events.count(name)) {
        events.insert(std::make_pair(name, EventTask(name)));
        DeviceLoop::loop.addDevice(&events[name]);
    }
    if (!events[name].froms.count(from)) {
        events[name].froms.insert(from);
        DeviceSubscribeManager::r.add(&events[name], from);
    }
}

void EventTask::remove(std::string name, MessageId from)
{
    if (events.count(name)) {
        if (events[name].froms.count(from)) {
            DeviceSubscribeManager::r.removeSubscribe(&events[name], from);
            events[name].froms.erase(events[name].froms.find(from));
        }
        if (events[name].froms.size() == 0) {
            DeviceLoop::loop.removeDevice(&events[name]);
            events.erase(events.find(name));
        }
    }
}


void TimedLoop::init()
{
    loop = new TimedLoop();
    loop->run();
}

void TimedLoop::addTask(std::string name, TimedTask* newTask)
{
    dlog("Adding new task\n");
    auto t = std::make_pair(name, newTask);
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
            dlog("Running task '%s'\n", kv.second->task.c_str());
            if (task.is_null()) {
                elog("Invalid timed event\n");
                continue;
            }
            Task* t = new Task(task["value"], task["name"]);
            t->run();
        }
    }
    Timer::delay(1000);
    return true;
}

TimedLoop::TimedLoop()
{
    dlog("Init timed loop\n");
    for (auto& el : JsonFile::timedEvents.j.items()) {
        dlog("Adding event %s\n", el.value()["name"].get<std::string>().c_str());
        addTask(el.value()["name"], new TimedTask(el.value()));
    }
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

template<typename T>
static T cast(json& j)
{
    if (j.is_string()) {
        return std::stod(j.get<std::string>());
    }
    return j.get<T>();
}

void TimedTask::updateJson(json& j)
{
    if (j.contains("name")) {
        name = j["name"];
    } else {
        elog("No name\n");
    } if (j.contains("minutes")) {
        minutes = cast<uint32_t>(j["minutes"]);
    } else {
        elog("No time value\n");
    } if (j.contains("seconds")) {
        seconds = cast<uint32_t>(j["seconds"]);
    } else {
        elog("No time value\n");
    } if (j.contains("type")) {
        type = strToType(j["type"]);
    } else {
        elog("No type");
    } if (j.contains("hours")) {
        hours = cast<uint32_t>(j["hours"]);
    } else {
        elog("No hours");
    } if (j.contains("days")) {
        days = cast<uint32_t>(j["days"]);
    } else {
        elog("No days");
    } if (j.contains("enabled")) {
        enabled_ = j["enabled"];
    } else {
        elog("No hours");
    } if (j.contains("task")) {
        task = j["task"];
        dlog("'%s'\n", task.c_str());
    } else {
        elog("No task");
    }
    dlog("\n");
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
            uint64_t value = (minutes*60*1000 + hours*60*60*1000 + seconds*1000);
            dlog("Time value %u > %u\n", currentTimeMs() - startTime_, value);
            if (value != 0 && currentTimeMs() - startTime_ > value) {
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
            if (currentMinute > (hours*60*60 + minutes) && currentMinute < (hours*60*60 + minutes) + 5 && startTime_ != day) {
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
            uint64_t timeToRun = (hours*60*60 + minutes + days*24*60);
            if (currentMinute > timeToRun && currentMinute < timeToRun + 5 && startTime_ != weekDay) {
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
    return duration.count() / 1000;
}

TimedLoop* TimedLoop::loop;

std::unordered_map<std::string, TimedTask*> TimedLoop::tasks;
