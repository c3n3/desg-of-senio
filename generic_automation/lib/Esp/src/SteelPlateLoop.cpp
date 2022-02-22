#include "../include/SteelPlateLoop.hpp"
#include "../include/WifiReceiver.hpp"
#include "../include/WifiSender.hpp"
#include "../include/CapabilitiesList.hpp"
#include "soc/rtc_wdt.h"

using namespace genauto;

WifiReceiver* rec;

WifiSender s("http://192.168.1.21");

void genauto::runSteelPlateLoop()
{
    xTaskCreatePinnedToCore(
        steelPlateLoop,
        "steel plate loop",
        1000,
        NULL,
        1,
        NULL,
        0
    );
}

void genauto::steelPlateLoop(void* data)
{
    rec = WifiReceiver::getReceiver();
    while (true)
    {
        continue;
        vTaskDelay(500 / portTICK_PERIOD_MS);
        { // Wifi rec
            auto msgPtr = rec->tryGet();
            if (msgPtr != nullptr) {
                auto& list = CapabilitiesList::subscriberList;
                for (int i = 0; i < list.getSize(); i++) {
                    StringBuilder sb(1000);
                    msgPtr->toString(sb);
                    dlog("Got %s\n", sb.getString());
                    list.getList()[i]->receive(msgPtr);
                }
            }
        }
        { // Wifi send
            auto& pubList = CapabilitiesList::publisherList;
            for (int i = 0; i < pubList.getSize(); i++) {
                auto msgPtr = pubList.getList()[i]->tryGet();
                if (msgPtr != nullptr) {
                    StringBuilder sb(1000);
                    msgPtr->toString(sb);
                    dlog("Sent %s\n", sb.getString());
                    s.receive(msgPtr);
                }
            }
        }
    }
}
