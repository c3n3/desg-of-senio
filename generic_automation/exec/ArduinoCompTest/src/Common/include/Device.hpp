#ifndef __GENAUTO_DEVICE_HPP__
#define __GENAUTO_DEVICE_HPP__

#include <stdint.h>

namespace genauto {
    class Device {
    public:
        /**
         * @brief Id for minor type for message ids
         */
        const uint8_t minorId;

        /**
         * @brief Do something
         */
        virtual void execute() = 0;
    };
}

#endif
