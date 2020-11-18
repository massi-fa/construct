#include "wifi.h"
#include <Arduino.h>

void setup() {
  
  connection();
  
}

void loop() {
  ArduinoOTA.handle();
  
}