#include "../include/TimedPublisher.hpp"


TimedPublisher::TimedPublisher(unsigned long interval, MessageId id)
    : interval_(interval), time_(millis())
{
    msg.id() = id;
}

Message* TimedPublisher::tryGet()
{
    if (millis() - time_ > interval_) {
        time_ += interval_;
        return &msg;
    }
    return nullptr;
}
