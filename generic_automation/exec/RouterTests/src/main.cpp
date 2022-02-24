#include "StepperMotorMessage.hpp"
#include "Message.hpp"
#include "Log.hpp"
#include "HexStringSerializer.hpp"
#include "Map.hpp"
#include "Timer.hpp"
#include "Message.hpp"
#include "Queue.hpp"
#include "Subscriber.hpp"
#include "Router.hpp"
#include "Publisher.hpp"
#include <iostream>
#include <sstream>

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

/*#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>

HexStringSerializer serilizer(1000);

void send(Message* message)
{
    std::ostringstream os;
    serilizer.serialize(message);
    std::string willSend = std::string("http://192.168.1.56?d=") + serilizer.getBuffer();
    std::cout << willSend << "\n";
    os << curlpp::options::Url(willSend);

}*/

class dummyPublisher : public Publisher{
    public:
    Message msg;
        Message* tryGet()
        {
            return &msg;
        }
};

class dummySubscriber : public Subscriber{
    public:
        void recieve(Message* msg)
        {
            std::cout << "Message Major: " << msg->id().getMajor() << "\n";
            std::cout << "Message Minor: " << msg->id().getMinor() << "\n";
        }
};

Message message;

int main()
{
        Router route;
        dummyPublisher* pub;
        dummySubscriber* sub;
        route.addPublisher(pub);
        route.Subscribe(sub, message.id());
        route.Execute();
}