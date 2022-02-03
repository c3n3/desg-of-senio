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

    float val;
    // val = *(float*)0xff;
    val = 0;
    MessageId m(0,0);
    // serilizer.serialize(&m);
    uint8_t* buffer = (uint8_t*)&m;
    for (int i = 0; i < sizeof(m); i++) {
        dlog("%x-", buffer[i]);
    }
    dlog("\n");
    dlog("sizeof(StepperMotorMessage) %d\n", sizeof(StepperMotorMessage));
    dlog("sizeof(MessageId) %d\n", sizeof(MessageId));
    dlog("sizeof(Message) %d\n", sizeof(Message));
    // dlog("sizeof(Message) %d\n", sizeof(m.size));
    // dlog("sizeof(Message) %d\n", sizeof(m.msgType));
    // dlog(serilizer.getBuffer());
}

StringBuilder sb(1000);

void loop()
{
    return;
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
