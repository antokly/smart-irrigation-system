#include "SISconfig.h"

// Measure Config
const uint32_t measureInterval = 3000;                  // 3 sec

// Network Settings
const char* ssid = "";
const char* password = "";

// MQTT Configs
const char* mqtt_server = " ";                          // IP of MQTT Broker
const int mqtt_port = 1883;                             // MQTT Port (By default : 1883)
const char* mqtt_send_topic = "/sending/topic";
const char* mqtt_reception_topic = "/reception/topic";
const uint32_t sendDataInterval = 10000;                // 3 sec
const uint32_t receptionInterval = 500;                 // Check MQTT reception every 0.5 sec