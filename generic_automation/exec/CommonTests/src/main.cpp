#include "StringBuilder.hpp"
#include "StepperMotorMessage.hpp"
#include "HexStringSerializer.hpp"
#include "Map.hpp"
#include "Message.hpp"
#include <iostream>

using namespace genauto;

void serializeTesting()
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

void mapTesting()
{
    Map<int, char> map;
    map.insert(Pair<int, char>(9, 'a'));
    std::cout << "Size = " << map.size() << "\n";
    map.insert(Pair<int, char>(3, 'y'));
    std::cout << "Size = " << map.size() << "\n";
    map.insert(Pair<int, char>(2, 'k'));
    std::cout << "Size = " << map.size() << "\n";
    map.insert(Pair<int, char>(10, 'b'));
    std::cout << "Size = " << map.size() << "\n";
    std::cout << "Value = " << map[9] << "\n";
    std::cout << "Value = " << map[3] << "\n";
    std::cout << "Value = " << map[2] << "\n";
    std::cout << "Value = " << map[10] << "\n";
    map.remove(9);
    std::cout << "Size = " << map.size() << "\n";
    std::cout << "Value = " << (map.contains(9) ? "True" : "False") << "\n";
    std::cout << "Value = " << map[3] << "\n";
    std::cout << "Value = " << map[2] << "\n";
    std::cout << "Value = " << map[10] << "\n";
}

int main()
{
  //serializeTesting();
  mapTesting();
}