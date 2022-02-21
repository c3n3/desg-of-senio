#ifndef __GENERIC_AUTOMATION_BUTTONDEVICE_HPP__
#define __GENERIC_AUTOMATION_BUTTONDEVICE_HPP__

#include "../../Common/include/Publisher.hpp"
#include "../../Common/include/Device.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include <stdint.h>

namespace genauto
{
    /**
     * @brief Abstract message
     */
    class ButtonDevice : public Publisher, public Device
    {
    private:
        uint8_t pinNumber;
        bool pressed_ = false;
        unsigned long lastTime = 0;
        bool send = false;
        ButtonMessage *bMsg = ButtonMessage(NULL);

    public:
        /**
         * @brief Construct a new Button Device object
         *
         * @param pinNumber
         */
        ButtonDevice(uint8_t pinNumber, minor_t minorId);

        /**
         * @brief executes the purpose of the Button class
         *
         */
        void execute();

        /**
         * @brief 
         * 
         * @return Message* 
         */
        Message *tryGet();
    };

    template <int PIN>
    class ButtonDeviceInst : public ButtonDevice
    {
    public:
        static ButtonDeviceInst<PIN> *self;
        static unsigned long time;

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
                ButtonDeviceInst<PIN>::time = millis();
            }
        }
    };
}

#endif