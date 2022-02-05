#include "../include/WifiReceiver.hpp"

#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include "../include/config.hpp"

using namespace genauto;


/*Put your SSID & Password*/
const char *ssid = SSID; // Enter SSID here
const char *password = PASSWORD;      //Enter Password here

WifiReceiver* WifiReceiver::receiver = nullptr;

WebServer server(80);

static void doNothing()
{
    server.send(200, "text/html", "");
}

WifiReceiver::WifiReceiver()
    : serializer(sizeof(msgBuffer)),
    cur(msgBuffer), gotMsg(false)
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", WifiReceiver::handleConnect);
    server.onNotFound(doNothing);
    server.begin();
}

WifiReceiver* WifiReceiver::getReceiver()
{
    if (receiver == nullptr) {
        receiver = new WifiReceiver();
    }
    return receiver;
}

void WifiReceiver::handleConnect()
{
    if (server.hasArg("d"))
    {
        String arg = server.arg("d");
        Serial.println(arg);
        if (receiver->serializer.parse(
            (const uint8_t*)arg.c_str(),arg.length())
            == HexStringSerializer::Failure)
        {
            Serial.println("Parsing failed");
        }
        receiver->gotMsg = true;
        Serial.println("GOT");
    }
    server.send(200, "text/html", "");
    Serial.println("Done");
}

Message* WifiReceiver::tryGet()
{
    server.handleClient();
    if (receiver->gotMsg && receiver->serializer.deserialize(
        &cur) == HexStringSerializer::Success)
    {
        dlog("\n");
        receiver->gotMsg = false;
        return &cur;
    }
    return nullptr;
}
