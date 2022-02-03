#ifndef __GENAUTO_WIFI_RECEIVER_HPP__
#define __GENAUTO_WIFI_RECEIVER_HPP__

#include "../../Common/include/Publisher.hpp"
#include "../../Common/include/Queue.hpp"
#include "../../Common/include/HexStringSerializer.hpp"

namespace genauto {
    class WifiReceiver : public Publisher {
        // TODO: This just needs to be the max size of a message
        HexStringSerializer serializer;
        Message* cur;
        uint8_t msgBuffer[100]; // TODO: Is this the max size?
        static void handleConnect();
        bool gotMsg;
        WifiReceiver();
        static WifiReceiver* receiver;
    public:
        static WifiReceiver* getReceiver();
        Message* tryGet();
    };
}

#endif
