/* Le but de ce programme est de nous donner 
la mesure de l'humiditié par le sensor toutes les 1 s */
// Just with WiFi classes sufficient

#include <Arduino.h>
#include "Sensors.h"
#include "Actuators.h"
#include "Network.h"

void setup(void)
{
  //Set the baudrate to 115200
  Serial.begin(115200);

  //Pump init
  pump_init();

  //network init
  network_setup();
}

void loop(void)
{
  //Measure Humidity with Sensors
  sensor_data_acquisition();

  //Irrigation
  pump_irrigation_automation();
}