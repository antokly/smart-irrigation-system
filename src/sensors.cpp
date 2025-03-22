#include "sensors.h"

const int sensor_pin = 35;  /* Soil moisture sensor pin */

// Measure
uint8_t get_sensor_data(void)
{
  uint8_t soil = 0;
  uint8_t humidity = 0;

  // TODO : Sensor Calibration Needed
  // Collect Data from Sensor
  soil = analogRead(sensor_pin); // read the data
  humidity = map(soil, 0, 200, 0, 100); //((sensor_analog/1900.00) * 100);

  return humidity;
}