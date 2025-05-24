#ifndef DEF_CONFIG
#define DEF_CONFIG

#include <Arduino.h>

/* LOGS */
#define COM_LOG_ENABLE

// Network Settings
extern const char* ssid;
extern const char* password;

// Measures Config
extern const uint32_t readingMeasurePeriod;
extern const int samplesByMeasure;
#define MOISTURE_SENSOR_PIN 35 /* Soil moisture sensor pin */
#define MOISTURE_SENSOR_VCC 4

// MQTT Configs
extern const char* mqtt_server;
extern const int mqtt_port;
extern const char* mqtt_send_topic;
extern const char* mqtt_reception_topic;
extern const uint32_t sendDataInterval;
extern const uint32_t receptionInterval;

#endif