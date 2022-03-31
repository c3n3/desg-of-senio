#include "../include/SteelPlateLoop.hpp"
#include "../include/WifiReceiver.hpp"
#include "../include/SubscribeManager.hpp"
#include "../include/WifiSender.hpp"
#include "../include/CapabilitiesList.hpp"
#include "../include/config.hpp"
#include "soc/rtc_wdt.h"

using namespace genauto;

WifiReceiver* rec;

WifiSender s(SERVER_IP);

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
        { // Wifi rec
            auto msgPtr = rec->tryGet();
            if (msgPtr != nullptr) {
                auto& list = CapabilitiesList::subscriberList;
                for (int i = 0; i < list.getSize(); i++) {
                    list.getList()[i]->receive(msgPtr);
                }
            }
        }
        { // Wifi send
            auto& pubList = CapabilitiesList::publisherList;
            for (int i = 0; i < pubList.getSize(); i++) {
                auto msgPtr = pubList.getList()[i]->tryGet();
                if (msgPtr) {
                    s.syncSend(msgPtr);
                }
            }
        }
        SubscribeManager::router.execute();
    }
}
