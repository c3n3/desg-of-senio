#include "Arduino.h"
#include "src/Common/include/StringBuilder.hpp"

using namespace genauto;   

StringBuilder sb(1000);

void setup() {
    Serial.begin(115200);
    sb.appendString("Hello people!");
}

void loop() {
    Serial.println(sb.getString());
    delay(1000);
}
