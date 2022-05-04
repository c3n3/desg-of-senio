#include "../include/ShiftRegister.hpp"

using namespace genauto;

void genauto::shiftInit()
{
    pinMode(SERIAL_PIN, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(LATCH, OUTPUT);
}

void genauto::shitfReg(int pin, bool set)
{
    static uint8_t regs = 0x00;
    if (set)
        regs |= 0x01 << pin;
    else
        regs &= ~(0x01 << pin);
    shiftOut(SERIAL_PIN, CLOCK, MSBFIRST, regs);
    digitalWrite(LATCH, LOW);
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
}
