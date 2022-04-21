#include "../include/SwitchDevice.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include "../include/ShiftRegister.hpp"

#include <stdint.h>

using namespace genauto;

/**
 * @brief Construct a new genauto::Switch Device::Switch Device object
 * 
 * @param pinNumber 
 */
genauto::SwitchDevice::SwitchDevice(uint8_t pinNumber, minor_t minorId)
    : pinNumber(pinNumber),
    Subscriber(),
    Device(minorId)
{
}

/**
 * @brief Construct a new genauto::Switch Device::change State object
 * 
 */
void genauto::SwitchDevice::changeState()
{
    state = !state;
    dlog("state\n");
}

/**
 * @brief 
 * 
 */
void genauto::SwitchDevice::execute()
{
    Message *Msg = nextMessage();
    if (Msg != nullptr)
    {
        dlog("message received\n");
        if (Msg->type() == ButtonMessage::classMsgType)
        {
            dlog("buttonMessage\n");
            ButtonMessage *bMsg = (ButtonMessage *)Msg;
            if (bMsg->pressed() == true)
                changeState();  
        }
    }
    if (state)
    {
         shitfReg(pinNumber, HIGH);
         dlog("output the signal\n");
    }
    else shitfReg(pinNumber, LOW);
}


Subscriber* genauto::SwitchDevice::sub()
{
    return static_cast<Subscriber*>(this);
}

