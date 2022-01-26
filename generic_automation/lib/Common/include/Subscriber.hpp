#ifndef __GENAUTO_SUBSCRIBER_HPP__
#define __GENAUTO_SUBSCRIBER_HPP__

#include "Message.hpp"
#include "Queue.hpp"

namespace genauto {
    /**
     * @brief Subscriber can can be used to subscribe to a
     * message ID
     */
    class Subscriber {
        Queue<Message*> msgs_;
    public:

        /**
         * @brief Constructor
         */
        Subscriber(int queueSize);

        /**
         * @brief Receive some message
         *
         * @param msg
         */
        virtual void receive(Message* msg);
    };
}

#endif
