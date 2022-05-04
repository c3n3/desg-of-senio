#ifndef __GENAUTO_SUBSCRIBE_MANGER__
#define __GENAUTO_SUBSCRIBE_MANGER__

#include "../../Common/include/Device.hpp"
#include "../../Common/include/Router.hpp"
#include "../../Common/include/SubscribeMessage.hpp"

namespace genauto {
    class SubscribeManager : public Device, public Subscriber {
        SubscribeManager();

        void addSub(SubscribeMessage* msg);
        void removeSub(SubscribeMessage* msg);

        void addPub(SubscribeMessage* msg);
        void removePub(SubscribeMessage* msg);

    public:
        static void init();
        static SubscribeManager* manager;
        static Router router;
        void execute();
    };
}

#endif
