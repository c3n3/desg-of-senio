#include "Arduino.h"
#include "src/Esp/include/WifiReceiver.hpp"

using namespace genauto;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Message* msg = WifiReceiver::getReceiver()->tryGet();
    if (msg != nullptr) {
        Serial.print("Got message of size = "); Serial.println(msg->size);
    }
}
