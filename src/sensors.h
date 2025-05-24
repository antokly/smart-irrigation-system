#ifndef DEF_SENSOR
#define DEF_SENSOR

#include <Arduino.h>

void sensor_setup(int sensor_vcc_pin);
// Make a sensor data CPP template to integrate differents others sensors easily in the system
uint32_t readSensor(int sensor_pin, int sensor_vcc_pin, int samples_nb);

int calibrateMoisture(int rawValue, int dryValue, int wetValue);

#endif