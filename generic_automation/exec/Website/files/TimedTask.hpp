#ifndef __GENAUTO_TIMED_TASK_HPP__
#define __GENAUTO_TIMED_TASK_HPP__

#include "../json/json.hpp"
#include "../files/Thread.hpp"
#include "../lib/Common/include/Device.hpp"
#include "../lib/Common/include/Subscriber.hpp"
#include <unordered_map>
#include <set>
#include <chrono>

using namespace nlohmann;

namespace genauto {

    class TimedTask;

    class EventTask : public Device, public Subscriber {
        static std::unordered_map<std::string, EventTask> events;
        const std::string name;
        std::set<MessageId> froms;
        EventTask(std::string name);
        void execute();
    public:
        EventTask();
        void add(std::string name, MessageId from);
        void remove(std::string name, MessageId from);
    };

    class TimedLoop : public Thread {
        TimedLoop();
        static std::unordered_map<std::string, TimedTask*> tasks;
    public:
        static void init();
        void addTask(std::string name, TimedTask* newTask);
        void removeTask(std::string name);
        bool contains(std::string name);
        void updateTask(json& j);
        bool exec();
        static TimedLoop* loop;
    };

    class TimedTask {
        friend class TimedLoop;
        bool enabled_;
        uint64_t startTime_;
        uint64_t currentTimeMs();
        std::chrono::high_resolution_clock::time_point start_;
        std::chrono::duration<float> duration_;
    public:
        enum TimedType {
            Periodic,
            Weekly,
            Daily,
            Unknown
        };

        static TimedType strToType(std::string str);

        TimedTask(json& j);

        void updateJson(json& j);

        bool shouldExecute();

        void enable();

        std::string task;

        std::string name;

        TimedType type;

        uint32_t seconds;

        uint32_t minutes;

        uint32_t hours;

        uint32_t days;
    };
}

#endif
