#include "../include/SwitchDevice.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include "../../Common/include/SwitchMessage.hpp"
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
    shitfReg(pinNumber, state);
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
        else if (Msg->type() == SwitchMessage::classMsgType)
        {
            dlog("buttonMessage\n");
            SwitchMessage *bMsg = (SwitchMessage *)Msg;
            state = bMsg->on();
            shitfReg(pinNumber, state);
        } else {
            dlog("Unhandled message type 0x%x\n", Msg->type());
        }
    }
}


Subscriber* genauto::SwitchDevice::sub()
{
    return static_cast<Subscriber*>(this);
}

