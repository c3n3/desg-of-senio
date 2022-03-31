#ifndef __GENAUTO_DEVICE_HPP__
#define __GENAUTO_DEVICE_HPP__

#include <stdint.h>
#include "MessageId.hpp"
#include "Subscriber.hpp"
#include "Publisher.hpp"

namespace genauto {

    extern major_t deviceId;

    class Device {
    public:
        /**
         * @brief Id for minor type for message ids
         */
        const minor_t minorId;

        /**
         * @brief Do something
         */
        virtual void execute() = 0;


        Device(minor_t minorId);

        virtual Subscriber* sub();
        virtual Publisher* pub();
    };
}

#endif
