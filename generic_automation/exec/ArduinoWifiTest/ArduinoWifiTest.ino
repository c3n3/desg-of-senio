#include "Arduino.h"
#include "src/Common/include/Log.hpp"
#include "src/Esp/include/WifiReceiver.hpp"
#include "src/Common/include/StepperMotorMessage.hpp"
#include "src/Common/include/EncoderMessage.hpp"
#include "src/Esp/include/PwmDevice.hpp"
#include "src/Common/include/SubscribeMessage.hpp"
#include "src/Common/include/Log.hpp"
#include "src/Common/include/StringBuilder.hpp"
#include "src/Common/include/Timer.hpp"

#include "src/Esp/include/SteelPlateLoop.hpp"
#include "src/Esp/include/ExecLoop.hpp"

using namespace genauto;

#include "soc/rtc_wdt.h"


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

}

void loop()
{
    fireAK();
}
