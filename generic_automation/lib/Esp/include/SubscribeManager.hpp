#ifndef __GENAUTO_SUBSCRIBE_MANGER__
#define __GENAUTO_SUBSCRIBE_MANGER__

#include "../../Common/include/Device.hpp"
#include "../../Common/include/Router.hpp"

namespace genauto {
    class SubscribeManager : public Device, public Subscriber {
        Router* devRouter_;
    public:
        void execute();

        SubscribeManager(minor_t minor, Router* devRouter);
    };
}

#endif
