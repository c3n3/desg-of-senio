#include "Arduino.h"
#include "src/Esp/include/WifiReceiver.hpp"
#include "src/Common/include/StepperMotorMessage.hpp"

#define ARDUINO
#include "src/Common/include/Log.hpp"
#include "src/Common/include/StringBuilder.hpp"

using namespace genauto;

void setup()
{
    Serial.begin(115200);
    HexStringSerializer serilizer(1000);
}

StringBuilder sb(1000);

void loop()
{
    Message* msg = WifiReceiver::getReceiver()->tryGet();
    if (msg != nullptr) {
        Serial.print("Got message of size = "); Serial.println(msg->getSize());
        dlog("\n");
        if (msg->type() == StepperMotorMessage::classMsgType) {
        dlog("\n");
            StepperMotorMessage* step = (StepperMotorMessage*)msg;
        dlog("\n");
            step->toString(sb);
        dlog("\n");
            Serial.println(sb.getString());
        dlog("\n");
        }
    }
}
