#include "../include/SteelPlateLoop.hpp"
#include "../include/WifiReceiver.hpp"
#include "../include/SubscribeManager.hpp"
#include "../include/WifiSender.hpp"
#include "../include/CapabilitiesList.hpp"
#include "../include/config.hpp"
#include "soc/rtc_wdt.h"

using namespace genauto;

WifiReceiver* rec;


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
        SubscribeManager::router.execute();
    }
}
