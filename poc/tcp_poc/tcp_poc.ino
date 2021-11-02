#include <Arduino.h>
#include <WiFi.h>
#include <wifi_info.h>

const int PORT = 23;

WiFiServer server(PORT);

const int LED = 2;

void setup()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PSWD);
    Serial.begin(115200);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
    pinMode(LED, OUTPUT);
    server.begin();
}

WiFiClient cli;

unsigned long timedInt = millis();
const unsigned long d = 1000;
void loop()
{
    if (server.hasClient()) {
        if (!cli.connected()) {
            Serial.println("Connected!");
            cli = server.available();
        } else {
            Serial.println("Rejected!");
            server.available().stop();
        }
    }
    if (cli.connected() && (millis() - timedInt > d)) {
        cli.print("This is text over TCP?\n");
        timedInt = millis();
    }
}
