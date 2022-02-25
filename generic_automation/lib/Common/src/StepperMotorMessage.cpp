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

float& StepperMotorMessage::stepScale()
{
    return get<float>(stepScale_loc);
}


StepperMotorMessage::Mode& StepperMotorMessage::modeType()
{
    return get<Mode>(valueType_loc);
}
