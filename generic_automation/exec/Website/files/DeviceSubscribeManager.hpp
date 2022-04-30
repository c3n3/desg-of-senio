#ifndef __GENAUTO_DEVICE_SUBSCRIBE_MANAGER_HPP__
#define __GENAUTO_DEVICE_SUBSCRIBE_MANAGER_HPP__

#include "DeviceSubscriber.hpp"
#include "DeviceLoop.hpp"
#include "lib/Common/include/MessageId.hpp"
#include "lib/Common/include/Publisher.hpp"
#include "lib/Common/include/Publisher.hpp"
#include "lib/Common/include/Router.hpp"
#include "lib/Common/include/Map.hpp"
#include "lib/Common/include/StaticQueue.hpp"
namespace genauto {
    class DeviceSubscribeManager {
        static Map<major_t, DeviceSubscriber> map;
        class Pub : public Publisher {
            Message m;
        public:
            Pub();
            BufferQueue<400, 100> msgs;
            Message* tryGet();
        };
        static Pub pub;
    public:
        static Router r;
        static void init();
        static void removeSub(MessageId& to, MessageId from);
        static void addSub(MessageId& to, MessageId from);
        static void publish(Message* publish);
    };
}

#endif
