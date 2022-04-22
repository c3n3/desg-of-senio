#ifndef __GENAUTO_COMMAND_HPP__
#define __GENAUTO_COMMAND_HPP__

#include "../lib/Common/include/MessageId.hpp"
#include "../json/json.hpp"

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

        double value;

        MessageId id;

        typedef void(*CommandExec)(Command*, MessageId&);

        CommandExec execs[6];

        /**
         * @brief Functions for each command type
         */
        static void StepperRotate(Command*, MessageId);
        static void StepperSpeed(Command*, MessageId);
        static void On(Command*, MessageId);
        static void Off(Command*, MessageId);
        static void Delay(Command*, MessageId);
        static void PwmSet(Command*, MessageId);
    
    public:
        void execute();

        Command(MessageId& id, double value);

        Command(json j);

        json toJson();
    };
}

#endif
