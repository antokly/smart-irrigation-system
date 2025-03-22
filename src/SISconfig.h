#ifndef DEF_CONFIG
#define DEF_CONFIG

#include <Arduino.h>

/* LOGS */
#define COM_LOG_ENABLE

// Measures Config
extern const uint32_t measureInterval;

// Network Settings
extern const char* ssid;
extern const char* password;

// MQTT Configs
extern const char* mqtt_server;
extern const int mqtt_port;
extern const char* mqtt_send_topic;
extern const char* mqtt_reception_topic;
extern const uint32_t sendDataInterval;
extern const uint32_t receptionInterval;

#endif