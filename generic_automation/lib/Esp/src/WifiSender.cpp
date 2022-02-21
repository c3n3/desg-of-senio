#include "../include/WifiSender.hpp"
#include "../../Common/include/StringBuilder.hpp"
#include <string.h>
#include <WiFi.h>
#include <HTTPClient.h>

void WifiSender::send(void* data)
{
    StringBuilder* sb = (StringBuilder*)data;

    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(sb->getString());
        int httpResponseCode = http.GET();
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
    delete data;
    vTaskDelete(NULL);
}

WifiSender::WifiSender(const char* url)
    : url_(url), serializer_(200)
{}

void WifiSender::receive(Message* msg)
{
    serializer_.serialize(msg);
    StringBuilder* sb = new StringBuilder(strlen(serializer_.getBuffer()) + strlen(url_) + 10);
    sb->appendString(url_);
    sb->appendString("/_ps_?d=");
    sb->appendString(serializer_.getBuffer());
    sb->appendChar('\0');
    xTaskCreate(
        WifiSender::send,
        "SEND",
        1000,
        sb,
        1,
        NULL
    );
}