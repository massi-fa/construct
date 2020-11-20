#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "HoMeF_first"
#define STAPSK  "acquaiolo"
#endif

namespace connect{
void wifi_setup();
void ota_setup();
void loop();
void setup();
}