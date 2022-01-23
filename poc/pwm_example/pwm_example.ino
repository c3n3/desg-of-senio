const int PWM_FREQUENCY = 5000;
const int PWM_CHANNEL = 0;
const int PWM_RESOUTION = 8;
const int TRIGPIN = 13; // for pin 13

void setup() {
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOUTION); // setup PWM 
  ledcAttachPin(TRIGPIN, PWM_CHANNEL);
}

void loop() {
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 140; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(PWM_CHANNEL, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 140; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(PWM_CHANNEL, dutyCycle);   
    delay(15);
  }
}

/*

// the number of the LED pin
const int ledPin = 34;  // 34 corresponds to GPIO34

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
}
 
void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
    delay(15);
  }
}
*/
