#include "../include/MessageTypeRegistry.hpp"
#include "../include/StepperMotorMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

static MessageTypeRegistry<StepperMotorMessage::classMsgType> r;

StepperMotorMessage::StepperMotorMessage(uint8_t* buffer)
    : Message(buffer, msgSize)
{
    if (size_() != msgSize) {
        dlog("Error: buffer size mismatch, watch for segfault.\n");
    }

    // Set type in case this is a new buffer
    Message::type() = classMsgType;
}

float& StepperMotorMessage::value()
{
    return get<float>(value_loc);
}

uint8_t& StepperMotorMessage::direction()
{
    return get<uint8_t>(direction_loc);
}

StepperMotorMessage::Type& StepperMotorMessage::valueType()
{
    return get<Type>(valueType_loc);
}
