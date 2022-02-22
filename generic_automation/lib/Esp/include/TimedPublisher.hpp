#ifndef __GENAUTO_TIMED_PUBLISHER_HPP__
#define __GENAUTO_TIMED_PUBLISHER_HPP__

#include "../../Common/include/Publisher.hpp"
#include "../../Common/include/Message.hpp"
#include <stdint.h>

namespace genauto {
    class TimedPublisher : public Publisher {
        unsigned long interval_;
        unsigned long time_;
        Message msg;
    public:
        TimedPublisher(unsigned long interval, MessageId id);
        Message* tryGet();
    };
}

#endif
