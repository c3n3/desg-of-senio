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
        5000,
        NULL,
        1,
        NULL,
        0
    );
}

void genauto::steelPlateLoop(void* data)
{
    rec = WifiReceiver::getReceiver();
    dlog("\n");
    while (true)
    {
        { // Wifi rec
    dlog("\n");
            auto msgPtr = rec->tryGet();
    dlog("\n");
            if (msgPtr != nullptr) {
    dlog("\n");
                auto& list = CapabilitiesList::subscriberList;
    dlog("\n");
                for (int i = 0; i < list.getSize(); i++) {
    dlog("\n");
                    StringBuilder sb(1000);
    dlog("\n");
                    msgPtr->toString(sb);
    dlog("\n");
                    dlog("Got %s\n", sb.getString());
    dlog("\n");
                    list.getList()[i]->receive(msgPtr);
    dlog("\n");
                }
            }
        }
        { // Wifi send
    dlog("\n");
            auto& pubList = CapabilitiesList::publisherList;
    dlog("\n");
            for (int i = 0; i < pubList.getSize(); i++) {
    dlog("\n");
                auto msgPtr = pubList.getList()[i]->tryGet();
    dlog("\n");
                if (msgPtr != nullptr) {
    dlog("\n");
                    StringBuilder sb(1000);
    dlog("\n");
                    msgPtr->toString(sb);
    dlog("\n");
                    dlog("Sent %s\n", sb.getString());
    dlog("\n");
                    s.receive(msgPtr);
    dlog("\n");
                }
    dlog("\n");
            }
    dlog("\n");
        }
    dlog("\n");
    }
    dlog("\n");
}
