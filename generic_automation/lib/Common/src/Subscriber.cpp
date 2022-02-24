#include "../include/Subscriber.hpp"

using namespace genauto;

Subscriber::Subscriber()
{}

void Subscriber::receive(Message* msg)
{
    dlog("\n");
    msgs_.enqueue(msg);
    dlog("\n");
}
