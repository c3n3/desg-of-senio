#include "../include/StepperDevice.hpp"
#include "../include/Device.hpp"
#include <stdint.h>
#include <Stepper.h>


static const uint16_t stepsPerRevolution = 200;


genauto::StepperDevice::StepperDevice(uint8_t stepPin, uint8_t dirPin, uint8_t minorId)  
    : dirPin(dirPin),
    stepPin(stepPin),
    Subscriber(10),
    minorId(MinorId),
    myStepper(stepsPerRevolution, dirPin, stepPin)
{
}

void genauto::StepperDevice::execute()
{

}