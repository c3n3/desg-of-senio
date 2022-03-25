#include <AccelStepper.h>

#define dirPin 33
#define stepPin 32
#define motorInterfaceType 2
#define buttonPin 13

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  stepper.setMaxSpeed(900);
  pinMode(buttonPin, OUTPUT);
}

void loop() {
  stepper.setSpeed(800);
  stepper.run();
  digitalWrite(buttonPin, HIGH);
  delay(500);
  digitalWrite(buttonPin, LOW);
  delay(500);
}
