#ifndef DEF_MQTT_MAN
#define DEF_MQTT_MAN

#include "SISconfig.h"

#include <WiFi.h>
#include <PubSubClient.h>

void mqtt_setup(void);

// MQTT message posting on topic
void mqtt_send_data(const char* topic, const char* payload);

// Callback function to receive messages
// void callback(char* topic, byte* payload, unsigned int length);

// Connect to the MQTT broker
void reconnect(void);

#endif