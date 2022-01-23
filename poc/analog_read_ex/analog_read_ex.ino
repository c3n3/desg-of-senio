

const int analogReadPin = 39;
int ADC_VALUE = 0;
float voltage_value = 0.0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  ADC_VALUE = analogRead(analogReadPin); // reads in the analog input (0-4095)
  voltage_value = (ADC_VALUE * 3.3 ) / (4095); // converts the analog input to Voltage (0-3.3V)
  Serial.println(voltage_value);
  delay(1000);
}
