#ifndef __GENAUTO_PUBLISHER_HPP__
#define __GENAUTO_PUBLISHER_HPP__

#include "Message.hpp"

namespace genauto {
    class Publisher {
    public:
        virtual Message* tryGet() = 0;
    };
}

#endif
