#ifndef __GENAUTO_DEVICE_SUBSCRIBE_MANAGER_HPP__
#define __GENAUTO_DEVICE_SUBSCRIBE_MANAGER_HPP__

#include "DeviceSubscriber.hpp"
#include "DeviceLoop.hpp"
#include "lib/Common/include/MessageId.hpp"
#include "lib/Common/include/Publisher.hpp"
#include "lib/Common/include/Publisher.hpp"
#include "lib/Common/include/Router.hpp"
#include "lib/Common/include/Map.hpp"

namespace genauto {
    class DeviceSubscribeManager {
        static Map<major_t, DeviceSubscriber> map;
        static Router r;
        static DeviceLoop loop;
    public:
        static void removeSub(MessageId& to, MessageId from);
        static void addSub(MessageId& to, MessageId from);
    };
}

#endif
