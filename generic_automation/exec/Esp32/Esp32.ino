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

Router r;
DummyPub p0(MessageId(21, 41));
DummyPub p1(MessageId(21, 42));
DummyPub p2(MessageId(21, 42));
DummyPub p3(MessageId(21, 43));

DebugDevice d0(41);
DebugDevice d1(42);
DebugDevice d2(43);
WifiSender sender = WifiSender(SERVER_IP);

void setup()
{
    r.subscribe((Subscriber*)&d0, MessageId(21,d0.minorId));
    r.subscribe((Subscriber*)&d1, MessageId(21,d1.minorId));
    r.subscribe((Subscriber*)&d2, MessageId(21,d2.minorId));

    dlog("This is not a thing\n");

    rtc_wdt_protect_off();
    rtc_wdt_disable();
    disableCore0WDT();
    disableLoopWDT();
    Serial.begin(115200);
    delay(100);
    // r.addPublisher(&p0);
    // r.addPublisher(&p1);
    // r.addPublisher(&p2);
    // r.addPublisher(&p3);
    WifiReceiver::getReceiver();
    CapabilitiesList::init();
    dlog("Ip = %d\n", CapabilitiesList::capabilitiesList->ip());
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
    // r.execute();
    // d0.execute();
    // d1.execute();
    // d2.execute();
    // dlog("This is a thing\n");
    // delay(1000);
    steelPlateLoop(nullptr);
}
