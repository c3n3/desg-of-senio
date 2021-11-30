#include "../include/StepperMotorMessage.hpp"

using namespace genauto;

StepperMotorMessage::StepperMotorMessage(StepperMotorMessage::Type t, float v)
    : value(v), type(t), msgId(STEPPER_MOTOR_MESSAGE_ID)
{
}