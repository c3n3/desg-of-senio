#include "../include/PwmMessage.hpp"
#include "../include/Log.hpp"
#include "../include/MessageTypeRegistry.hpp"

using namespace genauto;

static MessageTypeRegistry<PwmMessage::classMsgType> r;

PwmMessage::PwmMessage(uint8_t* buffer)
    : Message(buffer, msgSize)
{
    if (size_() != msgSize) {
        dlog("Error: buffer size mismatch, watch for segfault.\n");
    }

    // Set type in case this is a new buffer
    Message::type() = classMsgType;
}

/**
         * @brief gets the value of the message
         *
         * @return the value of how much the Pwm has changed.
         */
int16_t& PwmMessage::dutyCycle()
{
    return get<int16_t>(dutyCycle_location);
}


bool& PwmMessage::onOff()
{
    return get<bool>(onOff_location);
}


