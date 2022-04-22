#ifndef __GENAUTO_TASK_HPP__
#define __GENAUTO_TASK_HPP__

#include <string>

namespace genauto {
    class Task {


        /**
         * @brief Run the task, execute commands
         */
        void execute();

        std::string toJson();
    };
}

#endif
