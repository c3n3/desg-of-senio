#include "Arduino.h"
#include "src/Esp/include/WifiReceiver.hpp"
#include "src/Common/include/StepperMotorMessage.hpp"
#include "src/Common/include/SubscribeMessage.hpp"
#include "src/Common/include/Log.hpp"
#include "src/Common/include/StringBuilder.hpp"
#include "src/Common/include/Timer.hpp"

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
        Serial.print("Got message of size = "); Serial.println(msg->size());
        if (msg->type() == StepperMotorMessage::classMsgType) {
            dlog("Got Stepper msg\n");
            StepperMotorMessage* step = (StepperMotorMessage*)msg;
            step->log();
        } else if (msg->type() == SubscribeMessage::classMsgType) {
            dlog("Got subscribe msg\n");
            SubscribeMessage* step = (SubscribeMessage*)msg;
            step->log();
        }
    }
}
