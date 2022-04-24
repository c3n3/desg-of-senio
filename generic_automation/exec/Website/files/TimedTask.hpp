#ifndef __GENAUTO_TIMED_TASK_HPP__
#define __GENAUTO_TIMED_TASK_HPP__

#include "../json/json.hpp"
#include "../files/Thread.hpp"
#include <unordered_map>
using namespace nlohmann;

namespace genauto {

    class TimedLoop : public Thread {
        TimedLoop();
        static std::unordered_map<std::string, TimedTask*> tasks;
    public:
        void addTask(TimedTask* newTask);
        void updateTask(json j);
        bool exec();
        static TimedLoop loop;
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

        TimedTask (json j);

        bool shouldExecute();

        void enable();

        std::string task;

        std::string name;

        TimedType type;

        uint64_t value;

        uint32_t secondaryValue;
    };
}

#endif
