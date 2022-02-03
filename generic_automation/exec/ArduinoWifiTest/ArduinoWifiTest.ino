#include "Arduino.h"
#include "src/Esp/include/WifiReceiver.hpp"
#include "src/Common/include/StepperMotorMessage.hpp"
#include "src/Common/include/StringBuilder.hpp"

using namespace genauto;

void setup()
{
    Serial.begin(115200);
}

StringBuilder sb(1000);

void loop()
{
    Message* msg = WifiReceiver::getReceiver()->tryGet();
    if (msg != nullptr) {
        Serial.print("Got message of size = "); Serial.println(msg->size);
        if (msg->msgType == StepperMotorMessage::classMsgType) {
            StepperMotorMessage* step = (StepperMotorMessage*)msg;
            step->toString(sb);
            Serial.println(sb.getString());
        }
    }
}
