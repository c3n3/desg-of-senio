// #include "../include/PwmMessage.hpp"

// using namespace genauto;

// const Message::msgType_t PwmMessage::classMsgType = MSG_TYPE('A', 'D');

// /**
//          * @brief Create a stepper motor message
//          *
//          * @param type Type of the message
//          * @param value The value for the type
//          */
// PwmMessage::PwmMessage(MessageId id, int16_t dutyCycle, bool onOff)
//     : id(id), dutyCycle_(dutyCycle), onOff_(onOff) Message(id, PwmMessage::classMsgType)
// {
// }

// /**
//          * @brief gets the value of the message
//          *
//          * @return the value of how much the Pwm has changed.
//          */
// void PwmMessage::setDutyCycle(int16_t dutyCycle)
// {
//     dutyCycle_ = dutyCycle;
// }

// /**
//          * @brief gets the value of the message
//          *
//          * @return the value of how much the Pwm has changed.
//          */
// uint16_t PwmMessage::getDutyCycle()
// {
//     return dutyCycle_;
// }


// /**
//          * @brief gets the value of the message
//          *
//          * @return uint16_t
//          */
// bool getOnOff()
// {
//     return onOff_;
// }

// /**
//          * @brief Set the Value object
//          * 
//          * @param value 
//          */
// void setOnOff(bool onOff)
// {
//     onOff_ = onOff;
// }


// /**
//          * @brief Convert to string
//          *
//          * @param sb
//          */
// void PwmMessage::toString(StringBuilder &sb)
// {
//     sb.appendString("{PwmMessage; ");
//     sb.appendString("Duty cycle: ");
//     sb.appendInt(dutyCycle_);
//     sb.appendString(", ");
//     id.toString(sb);
//     sb.appendChar('}');
// }
