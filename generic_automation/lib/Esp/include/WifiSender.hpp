#ifndef __GENAUTO_WIFI_SENDER_HPP__
#define __GENAUTO_WIFI_SENDER_HPP__

#include "../../Common/include/Subscriber.hpp"
#include "../../Common/include/Message.hpp"
#include "../../Common/include/HexStringSerializer.hpp"
#include "../../Common/include/StaticQueue.hpp"

namespace genauto {
    class WifiSender {
        HexStringSerializer serializer_;
        const char* url_;
        static void send(void* sb);
    public:
        void receive(Message* msg);
        WifiSender(const char* url);
    };
}

#endif
