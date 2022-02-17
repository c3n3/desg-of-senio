#include "../include/Subscriber.hpp"

using namespace genauto;

Subscriber::Subscriber(int queueSize) : msgs_(queueSize)
{}

void Subscriber::receive(Message* msg)
{
    msgs_.enqueue(msg);
}
