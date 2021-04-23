#include "wifi.h"
#include "mqtt.h"
#include <Arduino.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


/*
*   Channel 
*/


const char* channel0 = "dht";
const char* channel1 = "logs";
const char* channel2 = "lights";
// const char* channelBrightness = "lights/leds/brightness";

vector<const char*> subscriptions{ channel0, channel1, channel2 };




/*
* DEFINE E DECLARATION USEFUL TO DHT SENSOR
*/
#include <DHT.h>


DHT dht(D5,DHT22);
const long probingTime = 1*2*1000L;
float hum;  //Stores humidity value
float temp; //Stores temperature value

const char* channelCommands = "sensors/commands";
const char* clientName = "ESP--sensors";
void sense(){
    ostringstream s2, s1;
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    s1 << hum;
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    s2 << temp;
    Serial.println(" Celsius");
    string message = "Temperatura= " + s2.str() + "C^" + " Umidità= " + s1.str() + "%";
  
    mqtt::client.publish(channel0,message.c_str());
}


unsigned long lastRun = millis() ;
inline void mainLoop() {
  if (millis() - lastRun >= probingTime) {
    sense();
    lastRun = millis();
  }
}

/*************************************************************************************************************/



void ac_sp(){
  Serial.println("led acceso");
  digitalWrite(D4, HIGH);
};
void sp_ac(){
  digitalWrite(D4, LOW);
};





/*
*   Funzione gestione mqtt (topic=channel)  (Payload=message) 
*/


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic ");
    Serial.print(topic);
    Serial.print(": ");
    char* message = (char*) payload;
    message[length] = '\0';
    Serial.println(message);

    string messaggio= string(message);
    // add string terminator
    
    if(strcmp(messaggio.c_str(),"acceso")==0){
      ac_sp();
      mqtt::client.publish("logs","Hai acceso il led");
    }
    if(strcmp(messaggio.c_str(),"spento")==0){
      sp_ac();
      mqtt::client.publish("logs","Hai spento il led");
    }
}

/*
*  Setup Main
*/


void setup() {
  dht.begin();
  connect::setup();
  mqtt::setup(clientName, subscriptions, callback);
  pinMode(D4, OUTPUT);
}

/*
*  Loop Main
*/


void loop() {
  connect::loop();
  mqtt::loop();
  mainLoop();
}