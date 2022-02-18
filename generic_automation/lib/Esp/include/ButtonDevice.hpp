#ifndef __GENERIC_AUTOMATION_BUTTONDEVICE_HPP__
#define __GENERIC_AUTOMATION_BUTTONDEVICE_HPP__

#include "../../Common/include/Publisher.hpp"
#include "../../Common/include/Device.hpp"
#include <stdint.h>

namespace genauto
{
    /**
     * @brief Abstract message
     */
<<<<<<< HEAD
    class ButtonDevice : public Publisher, public Device {
        private:
            uint8_t pinNumber;
            bool pressed_;
            unsigned long lastTime = 0;
    public:
=======
    class ButtonDevice : public Publisher
    {
    private:
        uint8_t pinNumber;
        bool pressed_ = false;
        unsigned long lastTime = 0;
        bool send = false;
        ButtonMessage *bMsg = ButtonMessage::ButtonMessage(void);
>>>>>>> 6434d12e5bda437ccd4d5a317707e6d5db8a86e8

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

    template <int PIN>
    class ButtonDeviceInst : public ButtonDevice
    {
    public:
        static ButtonDeviceInst<PIN> *self;
        static unsigned long time = 0;

        ButtonDeviceInst()
        {
            pinMode(PIN, INPUT);
            attachInterrupt(digitalPinToInterrupt(PIN), isr, RISING);
            self = this;
        }

        static void isr()
        {
            if ((millis() - ButtonDeviceInst<PIN>::time) > 500)
            {
                ButtonDeviceInst<PIN>::self->pressed_ = true;
                ButtonDeviceInst<PIN>::time) = millis();
            }
        }
    }
}

#endif