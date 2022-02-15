#include <AccelStepper.h>

#define dirPin 2
#define stepPin 3
#define motorInterfaceType 2

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  stepper.setMaxSpeed(1000);
}

void loop() {
  stepper.setSpeed(400);
  stepper.runSpeed();
}
