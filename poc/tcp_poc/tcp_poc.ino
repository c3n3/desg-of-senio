#include <Arduino.h>
#include "wifi_info.h"
#include "src/Communication.hpp"

Communication comms(WIFI_SSID, WIFI_PSWD, SERVER_IP, SERVER_PORT);

void setup()
{
    Serial.begin(115200);
    Serial.println("Connecting now.");
    while (comms.connect() != Communication::Success)
    {
        Serial.println("Failed to connect");
        delay(5000);
    }
}
#define BUF_SIZE 1000

char buf[BUF_SIZE];

void loop()
{
    comms.send("This is a test");
    Communication::Result result = comms.receive(buf, sizeof(buf));
    switch (result)
    {
        case Communication::Success:
            Serial.println("Got data: ");
            Serial.println(buf);
            break;
        case Communication::NoData:
            Serial.println("No data");
            break;
        case Communication::DataExceededLength:
            Serial.println("Not enough buffer");
            break;
        case Communication::NoWifi:
            Serial.println("No wifi");
            break;
        default:
            Serial.println("Receive failed in some way");
            break;
    }
    delay(1000);
}