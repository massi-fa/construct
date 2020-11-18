#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "HoMeF_first"
#define STAPSK  "acquaiolo"
#endif


void wifi_setup();
void ota_setup();
void connection();