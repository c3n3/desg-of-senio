#include "../include/ButtonMessage.hpp"
#include "../include/Log.hpp"

using namespace genauto;

const msgType_t ButtonMessage::classMsgType = MSG_TYPE('A', 'C');

/**
         * @brief Create a stepper motor message
         *
         * @param type Type of the message
         * @param value The value for the type
         */
ButtonMessage::ButtonMessage(uint8_t* buffer)
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
bool& ButtonMessage::pressed()
{
    return get<bool>(pressed_location);
}
