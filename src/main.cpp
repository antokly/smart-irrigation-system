#include <Arduino.h>
<<<<<<< HEAD
#include "Sensors.h"
#include "Actuators.h"
#include "Network.h"
=======
#include "sensors.h"
#include "actuators.h"
#include "network_base.h"
#include "SISconfig.h"
#include "mqtt_manager.h"

uint8_t humidity = 0;
String humidityStr = " ";
uint32_t lastMeasureTime = 0;

/**
 * TODO:
 * 1. Connect the downlink Commands by MQTT with actions to execute (merge MQTT brange)
 * 2. Compute average value of measures on 10 cycles (in a tab) before activate pump
 * 3. Develop sensors structure templates to facilitate new interfacing
 * 4. Develop Python app on Broker to display data on RT graph and dashboards
 */
>>>>>>> branch_MQTT_com

void setup(void)
{
  //  Set the baudrate to 115200
  Serial.begin(115200);

  //  Pump init
  pump_init();

  //  Network init
  network_setup();

  //  MQTT setup
  mqtt_setup();

}

void loop(void)
{
<<<<<<< HEAD
  //Measure Humidity with Sensors
  sensor_data_acquisition();
=======
  // Make a timer for sensor data acquisition AND compute the mean of the datas collected during this time intervalle
  //  Humidity Measuring Data // TODO Structure to getData
  // MQTT Send Data
  if (millis() - lastMeasureTime >= measureInterval) {
    humidity = get_sensor_data();
    humidityStr = String(humidity);
    lastMeasureTime = millis();
  }
   
  // MQTT Send Data AND Callback Loop to receive commands
  mqtt_loop(humidityStr);

  //  Irrigation
  pump_irrigation(humidity);
>>>>>>> branch_MQTT_com

  delay(500);
}