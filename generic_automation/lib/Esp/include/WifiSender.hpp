#ifndef __GENAUTO_WIFI_SENDER_HPP__
#define __GENAUTO_WIFI_SENDER_HPP__

#include "../../Common/include/Subscriber.hpp"
#include "../../Common/include/Message.hpp"
#include "../../Common/include/HexStringSerializer.hpp"
#include "../../Common/include/StaticQueue.hpp"
#include "config.hpp"

namespace genauto {
    class WifiSender : public Subscriber {
        HexStringSerializer serializer_;
        const char* url_;
        static void send_(void* sb);
        WifiSender(const char* url);
    public:
        void receive(Message* msg);
        String syncSend(Message* msg);
        static WifiSender sender;
    };
}

#endif
