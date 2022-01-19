/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPin 32
#define stepPin 33
#define stepsPerRevolution 1000

// button definitions and ISR
const int interruptPin = 25;
volatile bool buttonFlag = false;
volatile int interruptOccurrences = 0;
int nInterrupts = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

//ISR that when called shows that the button has been pressed.
void IRAM_ATTR handleButtonInterrupt() {
  buttonFlag = true;
  Serial.println("in isr");
}

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // button stuff
  Serial.begin(115200);
  Serial.println("Button interrupts sketch begins");
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleButtonInterrupt, FALLING);

}

void loop() {
  Serial.println(buttonFlag);
  if (buttonFlag == true) {
    Serial.println("made it in the buttonFlag if");
    // Set the spinning direction counterclockwise:
    digitalWrite(dirPin, LOW);
    // Spin the stepper motor 1 revolution quickly:
    for (int i = 0; i < 2* stepsPerRevolution; i++) {
      Serial.println("hi");
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
    }
    buttonFlag = false;
    delay(1000);
  }
  /*
    // Set the spinning direction clockwise:
    digitalWrite(dirPin, HIGH);
    // Spin the stepper motor 1 revolution slowly:
    for (int i = 0; i < stepsPerRevolution; i++) {
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2000);
    }
    delay(1000);*/
  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);
  // Spin the stepper motor 1 revolution quickly:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  delay(1000);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(1000);
  /*
    // Set the spinning direction counterclockwise:
    digitalWrite(dirPin, LOW);
    //Spin the stepper motor 5 revolutions fast:
    for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
    }
    delay(1000);*/
}
