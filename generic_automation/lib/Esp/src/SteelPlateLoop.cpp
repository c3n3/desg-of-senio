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
    while (true)
    {
        auto& devList = CapabilitiesList::deviceList;
        for (int i = 0; i < devList.getSize(); i++) {
            devList.getList()[i]->execute();
        }
        { // Wifi rec
            auto msgPtr = rec->tryGet();
            if (msgPtr != nullptr) {
                auto& list = CapabilitiesList::subscriberList;
                for (int i = 0; i < list.getSize(); i++) {
                    msgPtr->log();
                    list.getList()[i]->receive(msgPtr);
                }
            }
        }
        { // Wifi send
            auto& pubList = CapabilitiesList::publisherList;
            for (int i = 0; i < pubList.getSize(); i++) {
                auto msgPtr = pubList.getList()[i]->tryGet();
                continue;
                if (msgPtr != nullptr) {
                    s.receive(msgPtr);
                }
            }
        }
    }
}
