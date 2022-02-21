#include "../include/Subscriber.hpp"

using namespace genauto;

Subscriber::Subscriber()
{}

void Subscriber::receive(Message* msg)
{
    msgs_.enqueue(msg);
}
