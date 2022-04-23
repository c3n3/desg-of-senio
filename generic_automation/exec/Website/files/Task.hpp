#ifndef __GENAUTO_TASK_HPP__
#define __GENAUTO_TASK_HPP__
#include "Command.hpp"
#include "Thread.hpp"
#include <string>
#include <vector>

namespace genauto {
    class Task : public Thread {
    public:
        /**
         * @brief Commands of the task
         */
        std::vector<Command> commands;

        /**
         * @brief Create task from json
         */
        Task(json& j);

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
