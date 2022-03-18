#ifndef __GENAUTO_SUBSCRIBER_HPP__
#define __GENAUTO_SUBSCRIBER_HPP__

#include "Message.hpp"
#include "BufferQueue.hpp"

namespace genauto {

    class SubscriberInterface {
    public:
        virtual void receive(Message* msg) = 0;
    };

    /**
     * @brief Subscriber can can be used to subscribe to a
     * message ID
     */
    class Subscriber : public SubscriberInterface {
        static constexpr uint16_t maxMsgSize = 30;
        uint8_t buffer_[maxMsgSize];
        Message msg_;
    protected:
        BufferQueue<maxMsgSize, 20> msgs_;
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

        Message* nextMessage();
    };
}

#endif
