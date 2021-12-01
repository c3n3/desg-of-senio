#include "../include/StepperMotorMessage.hpp"

using namespace genauto;

StepperMotorMessage::StepperMotorMessage(StepperMotorMessage::Type t, float v)
    : value_(v), type_(t), Message(STEPPER_MOTOR_MESSAGE_ID)
{
}

void StepperMotorMessage::toString(StringBuilder& sb)
{
    sb.appendString("{StepperMotorMessage; Type: ");
    if (type_ == Degree) {
        sb.appendString("Degree, ");
    } else {
        sb.appendString("Speed, ");
    }
    sb.appendString("Value: ");
    sb.appendFloat(value_);
    sb.appendChar('}');
}