#include <Arduino.h>
#include "sensor_manager.h"
#include "actuators.h"
#include "lcd_display.h"
#include "wifi.h"
#include "config_manager.h"
#include "mqtt.h"

SIS_Config sis_config;

/**
 * TODO:
 * 1. Connect the downlink Commands by MQTT with processes to execute
 * 2. Develop Python App to display datas on RT dashboards
 */

void setup(void)
{
  Serial.begin(115200);
  SPIFFS.begin(true);
  delay(1000);

  /* TODO: SPIFFS JSON Config file */
  bool hasFile = SPIFFS.exists("/cfg.json");
  Serial.println(hasFile ? "JSON present" : "JSON missing");

  // Initialize Settings from Flash
  if (!readConfigFromFlash(&sis_config)) {
    Serial.println("No valid config found in Flash Memory. Setting defaults...");
    if (setDefaultConfig(&sis_config)) {
      Serial.println("Default config set. Ready to write to Flash Memory...");
      if (writeConfigtoFlash(&sis_config)) {
        Serial.println("Config successfully written to Flash Memory.");
      } else {
        Serial.println("Error writing config to Flash Memory.");
      }
    } else {
      Serial.println("Failed to set default config.");
    }
  } else {
    Serial.println("Config successfully read from Flash Memory.");
  }

  // Actuators setup
  setupPump();

  // Wifi setup
  setupWifi(&sis_config);

  // MQTT setup
  setupMQTT(&sis_config);

}

void loop(void)
{
  float data;
  String data_str;
  unsigned long next_send_ts;

  // Browse each active sensor config
  for(int i = 0; i < SENSORS_NB; i++)
  {
    if(sis_config.sensor_list[i]->getType() != SENSOR_NONE) // if sensor is integrated and defined
    {
      // time to read sensor value
      if (millis() >= sis_config.sensor_list[i]->getLastReadTs() + sis_config.sensor_list[i]->getReadFreq()) {
        data = sis_config.sensor_list[i]->readSensorValue();
        data_str = String(data);
      }

      /* TODO : LCD 1602 Module to display data */
      displayLCD(data_str);
      
      // MQTT Process to post data on topic
      if (millis() >= sis_config.sensor_list[i]->getLastSendTs() + sis_config.sensor_list[i]->getSendFreq()) {
        processMQTT(&sis_config, data_str.c_str(), i);
        sis_config.sensor_list[i]->setLastSendTs(millis());
      }

      if(sis_config.sensor_list[i]->getType() == SENSOR_MOISTURE) {
        // Handle actuators functions of datas readed // Irrigation
        processPumpLogic(data);
      }
    }
  }

  // MQTT Receive Callback Loop to receive commands and parameters from App

  delay(10); // To avoid CPU overload
}