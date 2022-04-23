#include "Command.hpp"
#include "Common.h"
#include "../lib/Common/include/StepperMotorMessage.hpp"
#include "../lib/Common/include/PwmMessage.hpp"
#include "../lib/Common/include/ButtonMessage.hpp"
#include "../lib/Common/include/SwitchMessage.hpp"
#include <chrono>
#include <thread>

using namespace genauto;

void Command::runStepperRotate(Command* command)
{
    StepperMotorMessage msg;
    msg.id() = command->id;
    msg.type() = StepperMotorMessage::Degrees;
    msg.value() = command->value;
    sendTo(&msg);
}

void Command::runStepperSpeed(Command* command)
{
    StepperMotorMessage msg;
    msg.id() = command->id;
    msg.type() = StepperMotorMessage::Degrees;
    msg.value() = command->value;
    sendTo(&msg);
}

void Command::runOn(Command* command)
{
    SwitchMessage msg;
    msg.id() = command->id;
    msg.on() = true;
    sendTo(&msg);
}

void Command::runOff(Command* command)
{
    SwitchMessage msg;
    msg.id() = command->id;
    msg.on() = false;
    sendTo(&msg);
}

void Command::runDelay(Command* command)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(uint64_t(1000*command->value)));
}

void Command::runPwmSet(Command* command)
{
    PwmMessage msg;
    msg.id() = command->id;
    msg.dutyCycle() = command->value;
    msg.onOff() = true;
    sendTo(&msg);
}

    
void Command::execute()
{
    execs[type](this);
}

Command::Command(MessageId& id, double value)
    : id(id), value(value)
{}

Command::Command(json j)
{
    #define TYPE(x, T) if ((x) == (#T)) type = T
    if (j.contains("type")) {
        std::string t = j["type"];
        TYPE(t, Delay);
        else TYPE(t, On);
        else TYPE(t, Off);
        else TYPE(t, StepperRotate);
        else TYPE(t, StepperSpeed);
        else TYPE(t, PwmSet);
        else elog("Invalid type\n");
    } else {
        elog("Did not find type\n");
    }
    if (j.contains("value")) {
        value = j["value"];
    } else {
        elog("Did not find value\n");
    }
    #undef TYPE
}

json Command::toJson()
{
    json j;
    j["value"] = value;
    j["type"] = value;
    return j;
}

Command::CommandExec Command::execs[6] = {
    Command::runDelay,
    Command::runOn,
    Command::runOff,
    Command::runStepperRotate,
    Command::runStepperSpeed,
    Command::runPwmSet,
};