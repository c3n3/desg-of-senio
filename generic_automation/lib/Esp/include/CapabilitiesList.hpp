#ifndef __GENAUTO_DEVICE_LIST_HPP__
#define __GENAUTO_DEVICE_LIST_HPP__

#include "Device.hpp"
#include "Capabilities.hpp"
#include "../../Common/include/Subscriber.hpp"
#include "../../Common/include/Publisher.hpp"
#include "../../Common/include/StaticList.hpp"

namespace genauto {
    namespace CapabilitiesList {
        extern StaticList<Device*> deviceList;
        extern StaticList<Publisher*> publisherList;
        extern StaticList<Subscriber*> subscriberList;
        extern CapabilitiesMessage capabilitiesList;
        void init();
    }
}


#endif
