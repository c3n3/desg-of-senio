#ifndef __GENAUTO_SHIFT_REGISTER_HPP__
#define __GENAUTO_SHIFT_REGISTER_HPP__

#include <Arduino.h>

namespace genauto {
    static const uint8_t MAINS_SW = 0;
    static const uint8_t PW_SW14 = 1;
    static const uint8_t PW_SW15 = 2;
    static const uint8_t SW16 = 3;
    static const uint8_t SW17 = 4;
    static const uint8_t SW18 = 5;
    static const uint8_t SW19 = 6;
    static const uint8_t LED_SW = 7;
    static const uint8_t SERIAL_PIN = 13;
    static const uint8_t CLOCK = 17;
    static const uint8_t LATCH = 16;

    void shiftInit();

    void shitfReg(int pin, bool set);
}

#endif
