#include "../include/StepperMotorMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

const msgType_t StepperMotorMessage::classMsgType = MSG_TYPE('A', 'B');

StepperMotorMessage::StepperMotorMessage(uint8_t* buffer)
    : Message(buffer, msgSize)
{
    setBuffer(buffer);
    if (*size_ != msgSize) {
        dlog("Error: buffer size mismatch, watch for segfault.\n");
    }

    // Set type in case this is a new buffer
    Message::type() = classMsgType;
}

StepperMotorMessage::Type StepperMotorMessage::type()
{
    return type_();
}

StepperMotorMessage::Type StepperMotorMessage::value()
{
    return value_();
}

void StepperMotorMessage::toString(StringBuilder& sb)
{
    sb.appendString("{StepperMotorMessage; Type: ");
    if (valueType_() == Degree) {
        sb.appendString("Degree, ");
    } else {
        sb.appendString("Speed, ");
    }
    sb.appendString("Value: ");
    sb.appendFloat(value_());
    sb.appendString(", ");
    msgId_->toString(sb);
    sb.appendChar('}');
}
