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
#include "src/Common/include/Log.hpp"
#include "src/Esp/include/WifiReceiver.hpp"
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

#include "src/Esp/include/SteelPlateLoop.hpp"
#include "src/Esp/include/ExecLoop.hpp"

using namespace genauto;

#include "soc/rtc_wdt.h"


ButtonDeviceInst<14> bDev(1);
EncoderDevice eDev(26,25,2);
int16_t encVal = 0;
AnalogDevice aDev(36, 3);
uint16_t aVal;
const uint8_t LED_PIN = 13;
SwitchDevice sDev(13, 4);


void setup()
{
    rtc_wdt_protect_off();
    rtc_wdt_disable();
<<<<<<< HEAD
    //disableCore0WDT();
    //disableLoopWDT();
    Serial.begin(115200);
    delay(100);
    //WifiReceiver::getReceiver();
=======
    disableCore0WDT();
    disableLoopWDT();
    Serial.begin(115200);
    delay(100);
    WifiReceiver::getReceiver();
    runSteelPlateLoop();

>>>>>>> 599c9422b4c245f5481de77f9f76fbeaa4c76faf
}

void loop()
{
<<<<<<< HEAD
    bDev.execute();
    Message* bMsg = bDev.tryGet();
    ButtonMessage *butMsg = (ButtonMessage*)bMsg;
    if(bMsg == nullptr) {}
    else 
    {
      Serial.println("Button Pressed");
      sDev.receive((Message*)butMsg);
    }
    
    eDev.execute();
    Message* eMsg = eDev.tryGet();
    EncoderMessage *encMsg = (EncoderMessage*)eMsg;
    if(eMsg != nullptr) encVal = encMsg->value();
    //dlog("Encoder Value: %d\n", encVal);

    aDev.execute();
    Message* aMsg = aDev.tryGet();
    AnalogMessage *algMsg = (AnalogMessage*)aMsg;
    if(algMsg != nullptr) 
    {
      aVal = algMsg->value();
      //dlog("analog value: %d\n", aVal);
    }

    sDev.execute();
    
    
    delay(100);
=======
    // dlog("Here\n");
    // sender.receive(&msg);
    // dlog("Here\n");
    // delay(1000);
    fireAK();
>>>>>>> 599c9422b4c245f5481de77f9f76fbeaa4c76faf
}
