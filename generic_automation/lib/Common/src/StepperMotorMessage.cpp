#include "../include/StepperMotorMessage.hpp"

using namespace genauto;

const Message::msgType_t StepperMotorMessage::classMsgType = MSG_TYPE('A', 'B');

StepperMotorMessage::StepperMotorMessage(
    MessageId id, StepperMotorMessage::Type t, float v)
    : value_(v), type_(t), Message(id, StepperMotorMessage::classMsgType)
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