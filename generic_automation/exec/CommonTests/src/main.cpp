#include "StringBuilder.hpp"
#include "StepperMotorMessage.hpp"
#include "TypedHexStringSerializer.hpp"
#include "MessageBuffer.hpp"
#include "Log.hpp"
#include "HexStringSerializer.hpp"
#include "Map.hpp"
#include "Message.hpp"
#include "Queue.hpp"
#include "Subscriber.hpp"
#include <iostream>
#include <sstream>

using namespace genauto;

void serializeTesting()
{
    TypedHexStringSerializer<StepperMotorMessage> serial;
    TypedHexStringSerializer<StepperMotorMessage> rec;

    StepperMotorMessage m(MessageId(1,1), StepperMotorMessage::Speed, 10);

    StringBuilder sb(1000);

    m.toString(sb);
    std::cout << "Before " << sb.getString() << "\n";

    serial.serialize(m);

    StepperMotorMessage m2(MessageId(0,0), StepperMotorMessage::Degree, 1110);
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

void queueTesting()
{
    Queue<int> q(10);
    int i = 0;
    while (q.enqueue(i++) != Queue<int>::Failure) {
    }
    int res;
    while (q.dequeue(res) != Queue<int>::Failure) {
        if (res %2 == 0) {
            q.enqueue(1);
        }
        std::cout << "Got " << res << "\n";
    }
}

void subTest()
{
    Map<MessageId, int> map;

    MessageId test(90,80);
    map[test];

}

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>

void testGet()
{

    // RAII cleanup
    curlpp::Cleanup myCleanup;

    // Send request and get a result.
    // Here I use a shortcut to get it in a string stream ...

    std::ostringstream os;
    HexStringSerializer serilizer(1000);
    StepperMotorMessage m(
        MessageId(90,1), StepperMotorMessage::Speed, 100);
    serilizer.serialize(&m);
    std::string willSend = std::string("http://172.20.10.11?d=") + serilizer.getBuffer();
    std::cout << willSend << "\n";
    os << curlpp::options::Url(willSend);

    std::string asAskedInQuestion = os.str();
    std::cout << asAskedInQuestion;
}

int main()
{
    Message16_t msg(MessageId(10, 20), MSG_TYPE('A', 'B'));
}