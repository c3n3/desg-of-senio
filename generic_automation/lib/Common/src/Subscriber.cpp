#include "../include/Subscriber.hpp"

using namespace genauto;

Subscriber::Subscriber() : msg_(buffer_, maxMsgSize)
{}

void Subscriber::receive(Message* msg)
{
    //dlog("Fomr thje tihbigs\n");
    if (!msgs_.enqueue(msg->getBuffer(), msg->getSizeSafe())) {
        elog("Failed enqueue of message\n");
    }
}

Message* Subscriber::nextMessage()
{
    Buffer b;
    if (msgs_.front(b)) {
        memcpy(msg_.getBuffer(), b.buffer, b.size);
        msgs_.dequeue();
        return &msg_;
    }
    return nullptr;
}
