#ifndef __GENAUTO_TASK_HPP__
#define __GENAUTO_TASK_HPP__
#include "Command.hpp"
#include <string>
#include <vector>

namespace genauto {
    class Task {
    public:
        /**
         * @brief Commands of the task
         */
        std::vector<Command> commands;

        /**
         * @brief Create blank task
         */
        Task(const char* name);

        /**
         * @brief Create task from json
         */
        Task(json& j);

        /**
         * @brief Run the task, execute commands
         */
        void execute();

        /**
         * @brief Create json from task
         *
         * @return std::string
         */
        json toJson();
    };
}

#endif
