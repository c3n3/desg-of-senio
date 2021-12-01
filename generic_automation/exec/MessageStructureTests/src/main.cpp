#include "StringBuilder.hpp"
#include "StepperMotorMessage.hpp"
#include "MessageSerializer.hpp"
#include "Message.hpp"
#include <iostream>

using namespace genauto;

int main()
{
    MessageSerializer<StepperMotorMessage> serial;
    MessageSerializer<StepperMotorMessage> rec;

    StepperMotorMessage m(StepperMotorMessage::Degree, 10);

    StringBuilder sb(1000);

    m.toString(sb);
    std::cout << "Before " << sb.getString() << "\n";

    serial.serialize(m);

    StepperMotorMessage m2(StepperMotorMessage::Speed, 1110);
    sb.clear();
    serial.deserialize(m2);
    m2.toString(sb);

    std::cout << "Result = " << rec.parse(serial.getBuffer(), serial.getSize()) << "\n";
    
    std::cout << "After: " << sb.getString() << "\n";
    std::cout << "Msg id = " << m2.getMsgId() << "\n";
}