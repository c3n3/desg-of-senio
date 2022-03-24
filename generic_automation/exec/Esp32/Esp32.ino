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
    WifiSender sender(SERVER_IP);
    dlog("Sending:\n");
    CapabilitiesList::capabilitiesList->log();

    ser.serialize(CapabilitiesList::capabilitiesList);
    uint8_t buffer[1000];
    Message msg(buffer, sizeof(buffer));

    ser.deserialize(&msg);

    CapabilitiesMessage real(msg.getBuffer(), msg.getBufferSize());
    real.log();

    String result = sender.syncSend(CapabilitiesList::capabilitiesList);
    if (result == "") {
        elog("Error, did not acquire device id. Maybe server ip is incorrect?\n");
    } else {
        genauto::deviceId = result.toInt();
        dlog("Acquired device id %x\n", genauto::deviceId);
    }
    msg.id() = MessageId(90, 20);
    msg.type() = 0x0001;
    // runSteelPlateLoop();
}

void loop()
{
    steelPlateLoop(nullptr);
}
