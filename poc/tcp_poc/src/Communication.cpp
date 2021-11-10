#include "Communication.hpp"

Communication::Communication(const char* ssid, const char* password, const char* ip, unsigned long port)
: serverIp(ip), ssid(ssid), password(password), serverPort(port)
{}

Communication::Result Communication::connectToServer()
{
    Serial.print("Connecting to server.");
    int infCounter = 0;
    while (!client.connect(serverIp, serverPort)) {
        Serial.print(".");
        infCounter++;
        if (infCounter > maxConnectAttempts) {
            Serial.println("\nFailed to connect to server.");
            return Result::CannotFindServer;
        }
        delay(500);
    }
    Serial.println("\nConnected to server.");
    return Success;
}

Communication::Result Communication::connectToWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    int infCounter = 0;
    Serial.print("Connecting to wifi.");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        infCounter++;
        if (infCounter > maxConnectAttempts) {
            Serial.println("\nFailed to connect to wifi.");
            return Result::NoWifi;
        }
        delay(500);
    }
    Serial.println("\nWifi connected!");
    return Success;
}

Communication::Result Communication::connect()
{
    Result res = connectToWifi();
    if (res != Success) return res;
    res = connectToServer();
    if (res != Success) return res;
    return Result::Success;
}

Communication::Result Communication::disconnect()
{
    client.stop();
}

Communication::Result Communication::send(const char* buf)
{
    client.print(buf);
    return Success;
}

Communication::Result Communication::receive(
    char* buf, unsigned long size)
{
    Serial.println(__LINE__);
    if (isConnected() == NoWifi) {
        return NoWifi;
    }
    Serial.println(__LINE__);
    if (!client.available()) {
        return NoData;
    }
    unsigned long readIn;
    readIn = client.readBytes(buf, size);
    if (readIn == -1) return NoData;
    Serial.print(readIn);
    if (readIn >= size) readIn = size - 1;
    // replace to make valid string
    buf[readIn] = '\0';
    return Success;
}

Communication::Result Communication::isConnected()
{
    if (WiFi.status() != WL_CONNECTED) return NoWifi;
    return Success;
}