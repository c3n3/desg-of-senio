#include "../include/SwitchDevice.hpp"
#include "../../Common/include/ButtonMessage.hpp"

#include <stdint.h>

using namespace genauto;

/**
 * @brief Construct a new genauto::Switch Device::Switch Device object
 * 
 * @param pinNumber 
 */
genauto::SwitchDevice::SwitchDevice(uint8_t pinNumber, minor_t minorId)
    : pinNumber(pinNumber),
    Subscriber(10),
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
}

/**
 * @brief 
 * 
 */
void execute()
{
    Message *Msg = NULL;
    if (msgs_.dequeue(Msg) == Queue<Message *>::Success)
    {
        if (Msg->type() == ButtonMessage::classMsgType)
        {
            ButtonMessage *bMsg = (ButtonMessage *)Msg;
            if (bMsg->pressed() == true)
                self.changeState();
        }
    }
    if (state) digitalWrite(pinNumber, HIGH);
    else digitalWtire(pinNumber, LOW);
}