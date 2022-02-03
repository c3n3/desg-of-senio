#include "../include/WifiReceiver.hpp"

#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

using namespace genauto;

WiFi.begin(ssid, password);

/*Put your SSID & Password*/
const char *ssid = "St. Isidores MHK Public"; // Enter SSID here
const char *password = "BeOurGuest";      //Enter Password here

WifiReceiver* WifiReceiver::receiver = nullptr;

WebServer server(80);

static void doNothing()
{}

WifiReceiver::WifiReceiver()
    : serializer(sizeof(msgBuffer)),
    cur(nullptr)
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
        receiver->serializer.parse(arg.c_str(),arg.length());
    }
    server.send(200, "text/html", "");
}

Message* WifiReceiver::tryGet()
{
    server.handleClient();
    if (receiver->serializer.deserialize(
        (Message*)msgBuffer) == HexStringSerializer::Success)
    {
        return (Message*)msgBuffer;
    }
    return nullptr;
}
