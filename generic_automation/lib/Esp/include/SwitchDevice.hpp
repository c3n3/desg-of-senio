#ifndef __GENERIC_AUTOMATION_SWITCH_DEVICE_HPP__
#define __GENERIC_AUTOMATION_SWITCH_DEVICE_HPP__

#include <stdint.h>
#include "../../Common/include/Device.hpp"
#include "../../Common/include/Subscriber.hpp"

namespace genauto {
    /**
     * @brief Abstract message
     */
    class SwitchDevice : public Subscriber, public Device {
    private:
        bool state = false;
        uint8_t pinNumber;
    public:

        /**
         * @brief Construct a new Switch Device object
         * 
         * @param pinNumber 
         */
        SwitchDevice(uint8_t pinNumber, minor_t minorId);

        /**
         * @brief 
         * 
         */
        void changeState();

        /**
         * @brief 
         * 
         */
        void execute();

        Subscriber* sub();
    };
}

#endif
