#ifndef __GENERIC_AUTOMATION_MESSAGE_PARSER_HPP__
#define __GENERIC_AUTOMATION_MESSAGE_PARSER_HPP__

#include <stdint.h>

namespace genauto {
    /**
     * @brief Parses messages from an incoming buffer
     */
    template<int SIZE>
    class MessageParser {
    public:
        
    private:
        uint8_t buffer[SIZE];
    };
}

// List all message declarations here
static const uint16_t STEPPER_MOTOR_MESSAGE_ID = 1;

#endif
