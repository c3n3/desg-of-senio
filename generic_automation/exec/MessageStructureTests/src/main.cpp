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

    for (int i = 0; i < serial.getSize(); i++) {
        std::cout << (char)serial.getBuffer()[i];
    }
    std::cout << "\n";

    m2.toString(sb);
    std::cout << "After deserialize: " << sb.getString() << "\n";


    std::cout << "Result = " << rec.parse(serial.getBuffer(), serial.getSize()) << "\n";
    sb.clear();
    rec.deserialize(m2);
    m2.toString(sb);
    std::cout << "After parse: " << sb.getString() << "\n";
}