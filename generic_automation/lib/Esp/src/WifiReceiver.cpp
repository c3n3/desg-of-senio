// Adaption from:
// https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/

#include "../include/WifiReceiver.hpp"
#include "../../Common/include/Timer.hpp"

#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include "../include/config.hpp"

using namespace genauto;


/*Put your SSID & Password*/
const char *ssid = WIFI_SSID; // Enter SSID here
const char *password = PASSWORD;      //Enter Password here

WifiReceiver* WifiReceiver::receiver = nullptr;

WebServer server(80);

static void doNothing()
{
    server.send(200, "text/html", "");
}

WifiReceiver::WifiReceiver()
    : serializer(sizeof(msgBuffer)),
    cur(msgBuffer, sizeof(msgBuffer)), gotMsg(false)
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
        dlog("Got %s\n", arg.c_str());
        if (arg == "") {
            elog("Invalid input\n");
        }
        if (receiver->serializer.parse(
            (const uint8_t*)arg.c_str(),arg.length())
            == HexStringSerializer::Failure)
        {
            dlog("Parsing failed\n");
        }
        receiver->gotMsg = true;
    }
    server.send(200, "text/html", "");
}   

Message* WifiReceiver::tryGet()
{
    Timer main("Handle Client");
    server.handleClient();
    if (receiver->gotMsg) {
        main.log();
        Timer t("Message Parse");
        if (receiver->serializer.deserialize(
            &cur) == HexStringSerializer::Success)
        {
            receiver->gotMsg = false;
            cur.log();
            t.log();
            return &cur;
        }
    }
    return nullptr;
}
