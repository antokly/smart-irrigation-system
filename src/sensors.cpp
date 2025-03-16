#include "sensors.h"

//Measure

const int sensor_pin = 35;  /* Soil moisture sensor pin */

uint8_t sensor_data_acquisition(void)
{
  uint8_t soil = 0;
  uint8_t humidity = 0;

  //TO DO etalonnage correct capteur
  // Collect Data from Sensor
  soil = analogRead(sensor_pin); // read the data
  humidity = map(soil, 0, 200, 0, 100); //((sensor_analog/1900.00) * 100);

  return humidity;
}