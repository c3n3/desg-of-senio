#ifndef __GENAUTO_COMMAND_HPP__
#define __GENAUTO_COMMAND_HPP__

#include "../lib/Common/include/MessageId.hpp"
#include "../json/json.hpp"

#include <vector>

using namespace nlohmann;

namespace genauto {
    class Command {
    public:
        enum CommandType {
            Delay = 0,
            On,
            Off,
            StepperRotate,
            StepperSpeed,
            PwmSet,
        };
    private:

        CommandType type;

        std::vector<double> values;

        MessageId id;

        typedef void(*CommandExec)(Command*);

        static CommandExec execs[6];

        /**
         * @brief Functions for each command type
         */
        static void runDelay(Command*);
        static void runOn(Command*);
        static void runOff(Command*);
        static void runStepperRotate(Command*);
        static void runStepperSpeed(Command*);
        static void runPwmSet(Command*);
    
    public:
        static std::string commandToString(Command::CommandType t);

        void execute();

        Command(json j);

        json toJson();
    };
}

#endif
