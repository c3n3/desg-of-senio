#include "Arduino.h"
#include "src/Common/include/Log.hpp"
#include "src/Esp/include/WifiReceiver.hpp"
#include "src/Common/include/StepperMotorMessage.hpp"
#include "src/Common/include/EncoderMessage.hpp"
#include "src/Esp/include/PwmDevice.hpp"
#include "src/Common/include/SubscribeMessage.hpp"
#include "src/Common/include/Log.hpp"
#include "src/Common/include/Timer.hpp"

#include "src/Esp/include/SteelPlateLoop.hpp"
#include "src/Esp/include/ExecLoop.hpp"
#include "src/Esp/include/WifiSender.hpp"
using namespace genauto;

#include "soc/rtc_wdt.h"

WifiSender sender("http://172.20.10.2");
Message msg;

void setup()
{
    rtc_wdt_protect_off();
    rtc_wdt_disable();
    disableCore0WDT();
    disableLoopWDT();
    Serial.begin(115200);
    delay(100);
    WifiReceiver::getReceiver();
    runSteelPlateLoop();
    msg.id() = MessageId(90, 20);
    msg.type() = MSG_TYPE('A','A');
}


void loop()
{
    msg.log();
    sender.receive(&msg);
    delay(1000);
    // fireAK();
}
