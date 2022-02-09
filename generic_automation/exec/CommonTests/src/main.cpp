#include "StringBuilder.hpp"
#include "StepperMotorMessage.hpp"
#include "SubscribeMessage.hpp"
#include "EncoderMessage.hpp"
#include "Message.hpp"
#include "Log.hpp"
#include "HexStringSerializer.hpp"
#include "Map.hpp"
#include "Timer.hpp"
#include "Message.hpp"
#include "Queue.hpp"
#include "Subscriber.hpp"
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>


using namespace genauto;

void serializeTesting()
{
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

HexStringSerializer serilizer(1000);

void send(Message* message)
{
    std::ostringstream os;
    serilizer.serialize(message);
    std::string willSend = std::string("http://172.20.10.11?d=") + serilizer.getBuffer();
    std::cout << willSend << "\n";
    os << curlpp::options::Url(willSend);

}

int main()
{
    Timer t("100 Volley");
    EncoderMessage encode;
    encode.id() = MessageId(100, 100);
    encode.value() = -1;

    for (int i = 0; i < 51; i++) {
        send(&encode);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    // StringBuilder sb(1000);
    // StepperMotorMessage msg;
    // msg.id() = MessageId(90, 10);
    // Message base = msg;

    // StepperMotorMessage msg2 = base;
    // std::cout << base.id().major << "\n";
    // std::cout << msg.id().major << "\n";
    // std::cout << msg.size() << "\n";
    // std::cout << base.size() << "\n";
    // std::cout << msg2.size() << "\n";
    // std::cout << msg2.id().major << "\n";

    // {
    //     Message* basePtr = &msg;
    //     basePtr->log();
    //     StepperMotorMessage* ptr = (StepperMotorMessage*)basePtr;
    //     ptr->log();
    // }
}