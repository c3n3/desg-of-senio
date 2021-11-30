#ifndef __GENERIC_AUTOMATION_MESSAGE_HPP__
#define __GENERIC_AUTOMATION_MESSAGE_HPP__

#include <stdint.h>

namespace genauto {
    /**
     * @brief Abstract message
     */
    class Message {
    protected:
        const uint16_t msgId;
    public:
        /**
         * @brief Checks to see if msgIds are the same
         *
         * @param id to check
         * @return true if ids the same 
         */
        bool isMsg(uint16_t id);
    };
}

const uint16_t STEPPER_MOTOR_MESSAGE_ID = 1;

#endif
