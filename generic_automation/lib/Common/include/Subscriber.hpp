#ifndef __GENAUTO_SUBSCRIBER_HPP__
#define __GENAUTO_SUBSCRIBER_HPP__

#include "Message.hpp"
#include "StaticQueue.hpp"

namespace genauto {
    /**
     * @brief Subscriber can can be used to subscribe to a
     * message ID
     */
    class Subscriber {
    protected:
        StaticQueue<Message*, 20> msgs_;
    public:

        /**
         * @brief Constructor
         */
        Subscriber();

        /**
         * @brief Receive some message
         *
         * @param msg
         */
        virtual void receive(Message* msg);
    };
}

#endif
