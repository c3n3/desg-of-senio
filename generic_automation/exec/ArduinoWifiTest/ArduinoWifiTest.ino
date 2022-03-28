//#include "Arduino.h"
//#include "src/Common/include/Log.hpp"
//#include "src/Esp/include/WifiReceiver.hpp"
//#include "src/Common/include/StepperMotorMessage.hpp"
//#include "src/Common/include/EncoderMessage.hpp"
//#include "src/Esp/include/PwmDevice.hpp"
//#include "src/Common/include/SubscribeMessage.hpp"
//#include "src/Common/include/Log.hpp"
//#include "src/Common/include/StringBuilder.hpp"
//#include "src/Common/include/Timer.hpp"
//
//#include "src/Esp/include/SteelPlateLoop.hpp"
//#include "src/Esp/include/ExecLoop.hpp"
//
//using namespace genauto;
//
//#include "soc/rtc_wdt.h"
//
//
//void setup()
//{
//    rtc_wdt_protect_off();
//    rtc_wdt_disable();
//    disableCore0WDT();
//    disableLoopWDT();
//    Serial.begin(115200);
//    delay(100);
//    WifiReceiver::getReceiver();
//    //runSteelPlateLoop();
//}
//
//void loop()
//{
//    //fireAK();
//    
//}

#include "Arduino.h"
//#include "src/Common/include/Log.hpp"
//#include "src/Esp/include/WifiReceiver.hpp"
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
//#include "src/Common/include/Log.hpp"
//#include "src/Common/include/StringBuilder.hpp"
#include "src/Common/include/Timer.hpp"

// #include "src/Esp/include/SteelPlateLoop.hpp"
// #include "src/Esp/include/ExecLoop.hpp"

using namespace genauto;

#include "soc/rtc_wdt.h"


// ButtonDeviceInst<14> bDev(1);
EncoderDevice eDev(26,25,2);
int16_t encVal = 0;
AnalogDevice aDev(39, 3);
uint16_t aVal;
const uint8_t LED_PIN = 13;
//SwitchDevice sDev(13, 4);
PwmDevice pDev(LED_PIN, 0, 5);
StepperDevice stepDev(32, 33, 6);


void setup()
{
    rtc_wdt_protect_off();
    rtc_wdt_disable();
    disableCore0WDT();
    disableLoopWDT();
    Serial.begin(115200);
    delay(100);
    //WifiReceiver::getReceiver();
    stepDev.setSpeed(0);
    StepperMotorMessage sMsg;
    sMsg.modeType() = StepperMotorMessage::Mode::DegreesSecond; // Degrees
    sMsg.value() = 100;
    sMsg.stepScale() = 360;
    stepDev.receive((Message*)&sMsg);
    sMsg.modeType() = StepperMotorMessage::Mode::Degrees;
    sMsg.value() = 360;
    stepDev.receive((Message*)&sMsg);
}

//void loop()
//{
//  stepDev.execute();
//}

void loop()
{
    // dlog("what is going on\n");
    // dlog("analog value: %d\n", analogRead(39));
    // Timer t("HI");
    // bDev.execute();
    // Message* bMsg = bDev.tryGet();
    // ButtonMessage *butMsg = (ButtonMessage*)bMsg;
    // if(bMsg == nullptr) {} //{dlog("button message nullptr\n");}
    // else 
    // {
    //   Serial.println("Button Pressed");
    //   //sDev.receive((Message*)butMsg);
    // }
    
    eDev.execute();
    Message* eMsg = eDev.tryGet();
    EncoderMessage *encMsg = (EncoderMessage*)eMsg;
    if(eMsg != nullptr) 
    {
      pDev.receive((Message*)encMsg);
      stepDev.receive((Message*)encMsg);
    }
    //dlog("Encoder Value: %d\n", encVal);

    aDev.execute();
    Message* aMsg = aDev.tryGet();
    AnalogMessage *algMsg = (AnalogMessage*)aMsg;
    if(algMsg != nullptr) 
    {
      aVal = algMsg->value();
      //dlog("analog value: %u\n", aVal);
    }

    //sDev.execute();

    pDev.execute();
    stepDev.execute();
    //t.log();
    // delay(100);
    // dlog("%d\n", analogRead(39));
}