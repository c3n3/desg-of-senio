#include "Arduino.h"
#include "src/Common/include/Log.hpp"
#include "src/Esp/include/WifiReceiver.hpp"
#include "src/Esp/include/WifiSender.hpp"
#include "src/Common/include/StepperMotorMessage.hpp"
#include "src/Common/include/EncoderMessage.hpp"
#include "src/Common/include/ButtonMessage.hpp"
#include "src/Common/include/AnalogMessage.hpp"
#include "src/Esp/include/ButtonDevice.hpp"
#include "src/Esp/include/AnalogDevice.hpp"
#include "src/Esp/include/EncoderDevice.hpp"
#include "src/Esp/include/SwitchDevice.hpp"
#include "src/Esp/include/StepperDevice.hpp"
#include "src/Esp/include/PwmDevice.hpp"
#include "src/Common/include/SubscribeMessage.hpp"
#include "src/Common/include/Log.hpp"
#include "src/Common/include/DebugDevice.hpp"
//#include "src/Common/include/StringBuilder.hpp"
#include "src/Common/include/Timer.hpp"
#include "src/Esp/include/CapabilitiesList.hpp"
#include "src/Esp/include/config.hpp"
#include "src/Esp/include/SteelPlateLoop.hpp"
#include "src/Esp/include/ExecLoop.hpp"

#include "src/Common/include/BufferQueue.hpp"


using namespace genauto;

#include "soc/rtc_wdt.h"

#include <vector>

Message msg;

HexStringSerializer ser(1000);

class DummyPub : public Publisher {
    Message m;
public:
    DummyPub(MessageId id)
    {
        m.id() = id;
    }
    Message* tryGet()
    {
        return &m;
    }
};

WifiSender sender = WifiSender(SERVER_IP);

void setup()
{
    rtc_wdt_protect_off();
    rtc_wdt_disable();
    disableCore0WDT();
    disableLoopWDT();
    Serial.begin(115200);
    delay(100);
    WifiReceiver::getReceiver();
    CapabilitiesList::init();
    dlog("Ip = %d\n", CapabilitiesList::capabilitiesList->ip());
    dlog("Sending:\n");
    CapabilitiesList::capabilitiesList->log();
    String result = sender.syncSend(CapabilitiesList::capabilitiesList);

    if (result == "") {
        elog("Error, did not acquire device id. Maybe server ip is incorrect?\n");
    } else {
        genauto::deviceId = result.toInt();
        dlog("Acquired device id %x\n", genauto::deviceId);
    }
}

void loop()
{
    runSteelPlateLoop();
    while (true) {
        fireAK();
    }
}
