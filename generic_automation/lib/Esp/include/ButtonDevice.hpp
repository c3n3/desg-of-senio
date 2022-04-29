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
    protected:
        uint8_t pinNumber;
        bool pressed_ = false;
        unsigned long lastTime = 0;
        unsigned long timeRise_ = 0;
        bool send = false;
        bool inited = false;
        ButtonMessage bMsg;
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

        Publisher* pub();
    };

    template <int PIN>
    class ButtonDeviceInst : public ButtonDevice
    {
    public:
        static ButtonDeviceInst<PIN> *self;
        static unsigned long timeRise;

        ButtonDeviceInst(minor_t minorId)
            : ButtonDevice(PIN, minorId)
        {
            pinMode(PIN, INPUT);
            attachInterrupt(digitalPinToInterrupt(PIN), isr, CHANGE);
            self = this;
        }

        static void isr()
        {
            if (digitalRead(PIN)) {
                ButtonDeviceInst<PIN>::timeRise_ = millis();
            } else {
                ButtonDeviceInst<PIN>::timeRise_ = 0;
            }
        }
    };
    template<int PIN> 
        ButtonDeviceInst<PIN> *ButtonDeviceInst<PIN>::self = nullptr;
    template<int PIN> 
        unsigned long ButtonDeviceInst<PIN>::time = 0;
}

#endif