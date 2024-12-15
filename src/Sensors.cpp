#include "Sensors.h"

//Measure
uint8_t soil = 0;
const int sensor_pin = 35;  /* Soil moisture sensor pin */
uint8_t humidity = 0;

void sensor_data_acquisition()
{
    //TO DO etalonnage correct capteur
  // Collect Data from Sensor
  soil = analogRead(sensor_pin); // read the data
  Serial.println(String("Soil val: ") + soil);
  humidity = map(soil, 0, 200, 0, 100); //((sensor_analog/1900.00) * 100);
  Serial.println(String("Value after mapped: ") + humidity);

}