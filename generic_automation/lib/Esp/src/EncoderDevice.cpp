#include "../include/EncoderDevice.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include <stdint.h>
#include <ESP32Encoder.h>

using namespace genauto;


/**
 * @brief Construct a new genauto::Pwm Device::pwm object
 *
 * @param pinNumber
 */
genauto::EncoderDevice::EncoderDevice(uint8_t pinA, uint8_t pinB, minor_t minorId)
    : pinA(pinA),
    pinB(pinB),
    Device(minorId),
    inited(false)
{
    
}

/**
 * @brief
 *
 */
void genauto::EncoderDevice::execute()
{
    if(!inited)
    {
        ESP32Encoder::useInternalWeakPullResistors=UP;
	    encoder.attachHalfQuad(pinA, pinB);
        encoder.clearCount();
        Serial.println("Encoder Start = " + String((int32_t)encoder.getCount()));
	    lastTime = millis();
        inited = true;
        //Serial.println("enc val: " + String((int32_t)encoder.getCount()) + "\n");
    }
    if ((millis() - lastTime) >= 250)
    {
        //Serial.println("enc val: " + String((int32_t)encoder.getCount()) + "\n");
        c = (int16_t)encoder.getCount();
        encoder.clearCount();
        //dlog("c: %d\n", c);
        lastTime = millis();
        if(count != c)
        {
            //dlog("count %d\n", count);
            count = c;
            flag = true;
        }
        eMsg.value() = count;
    }
}

/// As of right now, this class does not implement a Queue for encoder messages,
/// this shouldn't be a problem, but if it becomes a problem, we can implement
/// a Queue.


/**
 * @brief
 *
 * @return Message*
 */
Message *genauto::EncoderDevice::tryGet()
{
    if (flag)
    {
        flag = false;
        return &eMsg; // fixed, was returning message instead of address of msg
    }
    return nullptr;
}