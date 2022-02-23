#include "../include/ExecLoop.hpp"
#include "../include/AnalogDevice.hpp"
#include "../include/ButtonDevice.hpp"
#include "../include/CapabilitiesList.hpp"
#include "../include/EncoderDevice.hpp"
#include "../include/PwmDevice.hpp"
#include "../include/StepperDevice.hpp"
#include "../include/SwitchDevice.hpp"
#include "../include/WifiReceiver.hpp"
#include "../../Common/include/StringBuilder.hpp"
#include "../../Common/include/StepperMotorMessage.hpp"
#include "../../Common/include/SubscribeMessage.hpp"
#include "../../Common/include/EncoderMessage.hpp"
#include "../../Common/include/ButtonMessage.hpp"
#include "../../Common/include/Message.hpp"
#include "../../Common/include/Log.hpp"
#include "../../Common/include/HexStringSerializer.hpp"
#include "../../Common/include/Map.hpp"
#include "../../Common/include/Timer.hpp"
#include "../../Common/include/Queue.hpp"
#include "../../Common/include/Subscriber.hpp"

using namespace genauto;



void genauto::fireAK(){
    auto& devices = CapabilitiesList::deviceList;
    while (true) {
        for (int i = 0; i < devices.getSize(); i++) {
            devices.getList()[i]->execute();
        }
    }
}
