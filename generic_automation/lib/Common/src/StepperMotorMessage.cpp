#include "../include/MessageTypeRegistry.hpp"
#include "../include/StepperMotorMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

MESSAGE_ID_UNIQUE(StepperMotorMessage);

StepperMotorMessage::StepperMotorMessage(uint8_t* buffer, uint16_t bufferSize)
    : Message(buffer, bufferSize)
{}

StepperMotorMessage::StepperMotorMessage()
    : Message(msgSize)
{
    // Set type in case this is a new buffer
    type() = classMsgType;
}

float& StepperMotorMessage::value()
{
    return get<float>(value_loc);
}

float& StepperMotorMessage::stepScale()
{
    return get<float>(stepScale_loc);
}

StepperMotorMessage::Mode& StepperMotorMessage::modeType()
{
    return get<Mode>(valueType_loc);
}
