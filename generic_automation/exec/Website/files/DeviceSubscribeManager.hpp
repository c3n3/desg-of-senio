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
        static Map<MessageId, DeviceSubscriber> map;
        static Router r;
        static void removeSub(MessageId& to, MessageId from);
        static void addSub(MessageId& to, MessageId from);
        static void DeviceLoop loop;
    };
}

#endif
