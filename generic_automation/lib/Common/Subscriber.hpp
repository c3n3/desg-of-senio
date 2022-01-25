#ifndef __GENAUTO_SUBSCRIBER_HPP__
#define __GENAUTO_SUBSCRIBER_HPP__

#include "Message.hpp"

namespace genauto {
    class Subscriber {
    public:
        /**
         * @brief Receive some message
         *
         * @param msg
         */
        virtual void receive(Message* msg) = 0;
    };
}

#endif
