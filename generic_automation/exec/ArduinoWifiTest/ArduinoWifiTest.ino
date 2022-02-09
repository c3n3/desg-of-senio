#include "Arduino.h"
#include "src/Esp/include/WifiReceiver.hpp"
#include "src/Common/include/StepperMotorMessage.hpp"
#include "src/Common/include/EncoderMessage.hpp"
#include "src/Esp/include/PwmDevice.hpp"
#include "src/Common/include/SubscribeMessage.hpp"
#include "src/Common/include/Log.hpp"
#include "src/Common/include/StringBuilder.hpp"
#include "src/Common/include/Timer.hpp"

using namespace genauto;

PwmDevice p(13, 0);

void setup()
{
    Serial.begin(115200);
    HexStringSerializer serilizer(1000);
    p.setDutyCycle(50);
}

StringBuilder sb(1000);


void loop()
{
    Message* msg = WifiReceiver::getReceiver()->tryGet();
    if (msg != nullptr) {
        Serial.print("Got message of size = "); Serial.println(msg->size());
        if (msg->type() == EncoderMessage::classMsgType) {
            dlog("Got Encoder msg\n");
            EncoderMessage* step = (EncoderMessage*)msg;
            dlog("Increment: %d\n", step->value());
            step->log();
            p.receive(msg);
        }
    }
    p.execute();
}
