#include <wifi.h>

#include <Arduino.h>
#include <PubSubClient.h>

#include <vector>
#include <string>

using namespace std;

#include "mqtt.h"

#define MQTT_PSW "jIwCfS0QCMDjchp6QFlM2YGkiAUzj01rylTD1IkrkLAlQNhwiq79dDhl3ZKaPzre"

namespace mqtt {
    const char* server = "mqtt.flespi.io";
    const int port = 1883;
    const char* name;
    const char* user = MQTT_PSW;
    const char* password = "";

    vector<const char*> topics;

    const char* cLog;

    const char* connectMessage;
    const char* willTopic;
    const char* willMessage;

    byte willQoS = 0;
    boolean willRetain = true;

    WiFiClient wifiClient;
    PubSubClient client(wifiClient);

    boolean connect() {
        return client.connect(name, user, password, willTopic, willQoS, willRetain, willMessage);
    }

    void reconnect() {
        // Loop until we're reconnected
        while (!client.connected()) {
            Serial.println("Attempting MQTT connection...");
            // Attempt to connect
            if (connect()) {
                Serial.println("connected");
                // Once connected, publish an announcement and resubscribe
                client.publish(cLog, connectMessage);
                for (auto &t: topics) {
                    client.subscribe(t);
                }
            } else {
                Serial.println("failed, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 5 seconds");
                // Wait 3 seconds before retrying
                delay(3000);
            }
        }
    }

    void setup(const char* clientName, vector<const char*> subscriptions, callbackType callback) {
        name = clientName;
        topics = subscriptions;
        connectMessage = "Connesso";
        willMessage = "Disconesso";
        cLog = "logs";
        client.setServer(server, port);
        client.setCallback(callback);
    }
    
    void loop() {
        if (!client.connected()) {
            reconnect();
        }
        client.loop();
    }
}