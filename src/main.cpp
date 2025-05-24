#include <Arduino.h>
#include "sensors.h"
#include "actuators.h"
#include "wifi.h"
#include "sis_config.h"
#include "sendMQTT.h"

uint32_t humidity = 0;
String humidityStr = " ";
uint32_t lastMeasureTime = 0;

/**
 * TODO:
 * 1. Connect the downlink Commands by MQTT with actions to execute (merge MQTT branch)
 * 2. Improve sensor measures quality on 10 cycles (in a tab) before activate pump
 * 3. Develop sensors structure templates to facilitate new interfacing
 * 4. Develop Python App on Broker to display datas on RT graph and dashboards
 */

void setup(void)
{
  delay(500);
  Serial.begin(115200); // Set the baudrate to 115200
  sensor_setup(MOISTURE_SENSOR_VCC);
  pump_init(); // Pump init
  wifi_setup(); //  Network init
  mqtt_setup(); // MQTT setup
}

void loop(void)
{

  // Program Variables to declare : 
  // Data to display on an OLED Display
  // Next Reading Time
  // Next Sending Time
  // MeasuresPeriod sending from App
  // TimeToSleep (in seconds)

  // MQTT Send Data to App
  if (millis() - lastMeasureTime >= readingMeasurePeriod) {
    humidity = readSensor(MOISTURE_SENSOR_PIN, MOISTURE_SENSOR_VCC, samplesByMeasure);
    humidityStr = String(humidity);
    lastMeasureTime = millis();
  }
   
  // MQTT Send Data AND Callback Loop to receive commands
  mqtt_loop(humidityStr); //  Irrigation

  pump_irrigation(humidity);
  delay(100);
}