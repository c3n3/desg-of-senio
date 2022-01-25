#include "StepperMotorMessage.hpp"

using namespace genauto;

const Message::msgType_t StepperMotorMessage::msgType = {'A', 'B'};

StepperMotorMessage::StepperMotorMessage(
    MessageId id, StepperMotorMessage::Type t, float v)
    : value_(v), type_(t), Message(id)
{}

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
    sb.appendString(", ");
    id.toString(sb);
    sb.appendChar('}');
}