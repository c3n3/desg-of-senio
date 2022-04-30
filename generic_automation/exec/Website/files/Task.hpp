#ifndef __GENAUTO_TASK_HPP__
#define __GENAUTO_TASK_HPP__
#include "Command.hpp"
#include "Thread.hpp"
#include <string>
#include <set>
#include <vector>

namespace genauto {
    class Task : public Thread {
        static std::set<std::string> running_;
    public:

        /**
         * @brief Check if the task is already running
         *
         * @param test
         * @return true
         * @return false
         */
        static bool running(std::string test);

        /**
         * @brief The name of the task
         */
        const std::string name;

        /**
         * @brief Commands of the task
         */
        std::vector<Command> commands;

        /**
         * @brief Create task from json
         */
        Task(json& j, std::string name);

        /**
         * @brief Run the task, execute commands
         */
        bool exec();

        /**
         * @brief Create json from task
         *
         * @return std::string
         */
        json toJson();
    };
}

#endif
