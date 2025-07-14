/**
 * Default Project Config (First Loaded)
 */

#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

// Sensors Configuration
#define SENSOR1_PIN              35
#define SENSOR1_TYPE             SENSOR_MOISTURE
#define SENSOR2_PIN              34
#define SENSOR2_TYPE             SENSOR_HUMIDITY
#define SENSOR3_PIN              32
#define SENSOR3_TYPE             SENSOR_TEMPERATURE

// Actuators Configurations
#define PUMP_PIN                 33

// Network Settings
#define WIFI_SSID                "your_SSID"
#define WIFI_PASSWORD            "your_PASSWORD_for SSID"

// MQTT Configurations
#define MQTT_BROKER              ""
#define MQTT_PORT                1883
#define MQTT_DATA_TOPIC          "/esp32/data"
#define MQTT_COMMAND_TOPIC       "/esp32/command"
#define DATA_SEND_FREQ           6000
#define COMMAND_RECEPTION_FREQ   500

#endif