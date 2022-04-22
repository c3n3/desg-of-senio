#include "Command.hpp"
#include "Common.h"
#include "../lib/Common/include/StepperMotorMessage.hpp"
#include "../lib/Common/include/PwmMessage.hpp"
#include "../lib/Common/include/ButtonMessage.hpp"

using namespace genauto;

void Command::StepperRotate(Command* command, MessageId id)
{
    StepperMotorMessage msg;
    msg.type() = StepperMotorMessage::Degrees;
    msg.value() = command->value;
    sendTo(&msg);
}

void Command::StepperSpeed(Command* command, MessageId id)
{
    StepperMotorMessage msg;
    msg.type() = StepperMotorMessage::Degrees;
    msg.value() = command->value;
    sendTo(&msg);
}

void Command::On(Command* command, MessageId id)
{
    ButtonMessage 
}

void Command::Off(Command* command, MessageId id)
{

}

void Command::Delay(Command* command, MessageId id)
{

}

void Command::PwmSet(Command* command, MessageId id)
{

}

    
void Command::execute()
{

}

Command::Command(MessageId& id, double value)
{

}

Command::Command(json j)
{

}

json Command::toJson()
{

}
