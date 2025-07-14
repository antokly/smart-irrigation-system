#ifndef DEF_CONFIG
#define DEF_CONFIG

#include <Arduino.h>
#include "sensor_manager.h"
#include <ArduinoJson.h>
#include <FS.h>
#include "SPIFFS.h"
#include <Preferences.h>
#include "default_config.h"

/* LOGS */
#define COM_LOG_ENABLE

#define SENSORS_NB 3

extern Preferences preferences;

struct SIS_Config
{
  // deepsleep mode
  // time to sleep

  Sensor *sensor_list[SENSORS_NB];

  String wifi_ssid;
  String wifi_pwd;

  String mqtt_broker;
  uint16_t mqtt_port;
  String mqtt_data_topic;
  String mqtt_command_topic;
  uint32_t data_send_freq;
  uint32_t command_reception_frequency;
};

bool setDefaultConfig(SIS_Config *cfg);
bool writeConfigtoFlash(const SIS_Config *cfg);
bool readConfigFromFlash(SIS_Config *cfg);
bool readConfigFromJSON(SIS_Config *cfg);
bool areConfigsEqual(const SIS_Config *a, const SIS_Config *b);
bool writeConfigFile(const String& json);

#endif