#ifndef DEF_MQTT_MAN
#define DEF_MQTT_MAN

#include "sis_config.h"

#include <WiFi.h>
#include <PubSubClient.h>

extern WiFiClient espClient; // Connection layer
extern PubSubClient client; // Protocol layers

void mqtt_setup(void);

void mqtt_loop(const String data);

// MQTT message posting on topic
void mqtt_send_data(const char* topic, const char* payload);

// Callback function to receive messages
void callback(char* topic, byte* payload, unsigned int length);

// Connect to the MQTT broker
void reconnect(void);

#endif