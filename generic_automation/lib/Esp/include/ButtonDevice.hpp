#ifndef __GENERIC_AUTOMATION_BUTTONDEVICE_HPP__
#define __GENERIC_AUTOMATION_BUTTONDEVICE_HPP__

#include "../../Common/include/Publisher.hpp"
#include <stdint.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class ButtonDevice : public Publisher {
        private:
            uint8_t pinNumber;
            bool pressed_;
            unsigned long lastTime = 0;
    public:

        /**
         * @brief Construct a new Button Device object
         * 
         * @param pinNumber 
         */
        ButtonDevice() = 0;

        /**
         * @brief executes the purpose of the Button class
         * 
         */
        void execute();
    };

    template<int PIN>
    class ButtonDeviceInst : public ButtonDevice {

        ButtonDeviceInst()
        {
            // Init
        }

        static void isr()
        {
            // Do something
            // use PIN
        }
    }
}

#endif