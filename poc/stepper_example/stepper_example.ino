#include <AccelStepper.h>

#define dirPin 33
#define stepPin 32
#define motorInterfaceType 2

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  stepper.setMaxSpeed(900);
}

void loop() {
  stepper.setSpeed(800);
  stepper.run();
}
