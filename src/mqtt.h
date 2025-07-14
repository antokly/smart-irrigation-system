#ifndef DEF_MQTT_MAN
#define DEF_MQTT_MAN

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "sensor_manager.h"
#include "wifi.h"
#include "config_manager.h"
#include "default_config.h"

extern WiFiClient espClient; // Connection layer
extern PubSubClient client; // Protocol layers

// Callback function to receive commands
void callbackMQTT(char* topic, byte* payload, unsigned int length);
// Connect to the MQTT broker and topic
void reconnectMQTT(void);
// MQTT message to post on topic
void publishMQTT(const SIS_Config* cfg, const char* data, int i);
// MQTT Setup
void setupMQTT(SIS_Config* cfg);
// MQTT Loop Process
void processMQTT(SIS_Config *cfg, const char* data, int i);
#endif