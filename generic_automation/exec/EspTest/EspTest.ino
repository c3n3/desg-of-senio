#include "Arduino.h"
#include "src/Common/include/Log.hpp"
#include "src/Esp/include/WifiReceiver.hpp"
#include "src/Common/include/StepperMotorMessage.hpp"
#include "src/Common/include/EncoderMessage.hpp"
#include "src/Common/include/ButtonMessage.hpp"
#include "src/Esp/include/ButtonDevice.hpp"
#include "src/Esp/include/AnalogDevice.hpp"
#include "src/Esp/include/EncoderDevice.hpp"
#include "src/Esp/include/SwitchDevice.hpp"
#include "src/Esp/include/StepperDevice.hpp"
#include "src/Esp/include/ShiftRegister.hpp"
#include "src/Esp/include/PwmDevice.hpp"
#include "src/Common/include/SubscribeMessage.hpp"
#include "src/Common/include/Log.hpp"
#include "src/Common/include/Timer.hpp"

#include "src/Esp/include/SteelPlateLoop.hpp"
#include "src/Esp/include/ExecLoop.hpp"

using namespace genauto;

#include "soc/rtc_wdt.h"


// ButtonDeviceInst bDev<14>(1);


static StepperDevice stepper1(32, 33,  ConstantIds::Esp::NEW_IDS_START + 5);
static StepperDevice stepper2(26, 27,  ConstantIds::Esp::NEW_IDS_START + 6);
static StepperDevice stepper3(23, 25,  ConstantIds::Esp::NEW_IDS_START + 7);

StepperMotor motor(33, 32);


static const uint8_t PWM5_DIR = 22;
static const uint8_t PWM5_PWM = 21;


// static PwmDevice pwm1(21, 0, ConstantIds::Esp::NEW_IDS_START + 3);
// static PwmDevice pwm2(18, 0, ConstantIds::Esp::NEW_IDS_START + 4);

static ButtonDeviceInst<34> button1(ConstantIds::Esp::NEW_IDS_START);
static ButtonDeviceInst<35> button2(ConstantIds::Esp::NEW_IDS_START + 1);

void setup()
{
    rtc_wdt_protect_off();
    rtc_wdt_disable();
    disableCore0WDT();
    disableLoopWDT();
    Serial.begin(115200);
    delay(100);
    // WifiReceiver::getReceiver();
    shiftInit();
    stepper1.setSpeed(90);
    // pwm1.setDutyCycle(100);
    // pwm2.setDutyCycle(50);
    // motor.setSpeedDps(90);
}

bool on = false;

uint32_t timer;

void loop()
{
    if (button1.tryGet()) {
        dlog("Got\n");
    }
    button1.execute();
}
