#include "../include/WifiSender.hpp"
#include <string.h>
#include <WiFi.h>
#include <HTTPClient.h>

void WifiSender::send_(void* data)
{
    delete[] data;
}

WifiSender::WifiSender(const char* url)
    : url_(url), serializer_(100)
{}

String WifiSender::syncSend(Message* msg)
{
    String ret = "";
    serializer_.serialize(msg);
    uint16_t urlLen = strlen(url_);
    uint16_t dataLen = strlen(serializer_.getBuffer());
    const char* prefix = "/_ps_?d=";
    uint16_t prefixLen = strlen("/_ps_?d=");

    char* buffer = new char[urlLen + dataLen + prefixLen + 1];
    memcpy(buffer, url_, urlLen); 
    memcpy(buffer+urlLen, prefix, prefixLen); 
    memcpy(buffer+urlLen+prefixLen, serializer_.getBuffer(), dataLen+1); 
    if (WiFi.status() == WL_CONNECTED)
    {
        char* url = (char*)buffer;
        HTTPClient http;
        http.begin(url);
        int httpResponseCode = http.GET();
        ret = http.getString();
        if (httpResponseCode <= 0)
        {
            elog("Error: %d\n", httpResponseCode);
        }
        // Free resources
        http.end();
    }
    else
    {
        elog("Disconnected wifi\n");
    }
    // xTaskCreate(
    //     WifiSender::send,
    //     "SEND",
    //     2000,
    //     nullptr,
    //     1,
    //     NULL
    // );
    delete buffer;
    return ret;
}

void WifiSender::receive(Message* msg)
{
    syncSend(msg);
}