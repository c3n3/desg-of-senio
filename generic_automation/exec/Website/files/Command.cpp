#include "Command.hpp"
#include "Common.h"
#include "../lib/Common/include/StepperMotorMessage.hpp"
#include "../lib/Common/include/PwmMessage.hpp"
#include "../lib/Common/include/ButtonMessage.hpp"
#include "../lib/Common/include/SimpleMessages.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

using namespace genauto;

std::string Command::commandToString(Command::CommandType t)
{
    #define CASE(x) case x: return #x
    switch (t) {
        CASE(Delay);
        CASE(StepperRotate);
        CASE(StepperSpeed);
        CASE(On);
        CASE(Off);
        CASE(PwmSet);
        default: return "Unknown";
    }
    #undef CASE
}

void Command::runStepperRotate(Command* command)
{
    StepperMotorMessage msg;
    msg.id() = command->id;
    msg.modeType() = StepperMotorMessage::Degrees;
    msg.value() = command->values[0];
    msg.stepScale() = -1;
    sendTo(&msg);
}

void Command::runStepperSpeed(Command* command)
{
    StepperMotorMessage msg;
    msg.id() = command->id;
    msg.modeType() = StepperMotorMessage::DegreesSecond;
    msg.value() = command->values[0];
    msg.force() = command->values[1] != 0;
    msg.stepScale() = -1;
    sendTo(&msg);
}

void Command::runOn(Command* command)
{
    FlipMessage msg;
    msg.id() = command->id;
    msg.on() = true;
    sendTo(&msg);
}

void Command::runOff(Command* command)
{
    FlipMessage msg;
    msg.id() = command->id;
    msg.on() = false;
    sendTo(&msg);
}

void Command::runDelay(Command* command)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(uint64_t(1000*command->values[0])));
}

void Command::runPwmSet(Command* command)
{
    PwmMessage msg;
    msg.id() = command->id;
    msg.dutyCycle() = command->values[0];
    msg.onOff() = true;
    sendTo(&msg);
}

    
void Command::execute()
{
    std::cout << "Running " << commandToString(type) << " Value: " << values[0] << "\n";
    execs[type](this);
}

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
    } else {
        elog("Did not find type\n");
    }
    if (j.contains("values")) {
        for (auto& v : j["values"].items()) {
            values.push_back(v.value().get<double>());
        }
    } else {
        elog("Did not find value\n");
    }
    if (j.contains("major")) {
        id.major = j["major"].get<major_t>();
    } else {
        elog("Did not find major\n");
    }
    if (j.contains("minor")) {
        id.minor = j["minor"].get<minor_t>();
    } else {
        elog("Did not find minor\n");
    }
    #undef TYPE
}

json Command::toJson()
{
    json j;
    j["values"] = values;
    j["type"] = commandToString(type);
    j["major"] = id.major+0;
    j["minor"] = id.minor+0;
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