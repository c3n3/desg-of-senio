#include "StringBuilder.hpp"
#include "StepperMotorMessage.hpp"
#include "HexStringSerializer.hpp"
#include "Message.hpp"
#include <iostream>

using namespace genauto;

int main()
{
    HexStringSerializer<StepperMotorMessage> serial;
    HexStringSerializer<StepperMotorMessage> rec;

    StepperMotorMessage m(StepperMotorMessage::Speed, 10);

    StringBuilder sb(1000);

    m.toString(sb);
    std::cout << "Before " << sb.getString() << "\n";

    serial.serialize(m);

    StepperMotorMessage m2(StepperMotorMessage::Degree, 1110);
    sb.clear();
    serial.deserialize(m2);

    std::cout << "Result = " << rec.parse(serial.getBuffer(), serial.getSize()) << "\n";
    rec.deserialize(m2);
    m2.toString(sb);
    
    std::cout << "After: " << sb.getString() << "\n";
    std::cout << "Msg id = " << m2.getMsgId() << "\n";
}