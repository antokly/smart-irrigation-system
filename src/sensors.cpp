#include "sensors.h"

const uint32_t valueDry = 0;
const uint32_t valueWet = 0;

// For EMA filter
float ema_filtered = 0;        // Keep as a global or static variable
const float alpha = 0.1;       // EMA smoothing factor: lower = smoother, but slower response

void sensor_setup(int sensor_vcc_pin)
{
  pinMode(sensor_vcc_pin, OUTPUT);
  digitalWrite(sensor_vcc_pin, LOW);
}

// Exponential Moving Average filter
float filterEMA(float newValue, float lastValue, float alpha)
{
  return alpha * newValue + (1.0 - alpha) * lastValue;
}

uint32_t readSensor(int sensor_pin, int sensor_vcc_pin, int samples_nb)
{
  uint32_t value = 0;

  digitalWrite(sensor_vcc_pin, HIGH); // To avoid error on measure due to sensor supply perturbations

  delay(100); // Wait for stabilization

  // mean of collected sensor datas : moving average (" moyennage glissant ")
  uint32_t sum = 0;
  for(int i = 0; i < samples_nb; i++){
    sum += analogRead(sensor_pin); // get acquired sensor data
    delay(10); // short break to avoid reading too close
  }

  digitalWrite(sensor_vcc_pin, LOW);

  value = sum / samples_nb;

  // Apply EMA filter on raw analog value (inspired of Kalman filter)
  static bool first_reading = true;
  if (first_reading) {
    ema_filtered = value;
    first_reading = false;
  } else {
    ema_filtered = filterEMA(value, ema_filtered, alpha);
  }

  // calibration process : measure 2 times 1 dry and 1 wet and replace dry and wet values
  // Apply calibration after filtering
  // uint32_t calibrated_value = calibrateMoisture((uint32_t)ema_filtered, valueDry, valueWet);

  return ema_filtered;  // Return percentage (0–100)
}

// Calibrates raw sensor value to a percentage (0% = dry, 100% = wet)
// Requires prior measurement of raw values in dry and wet conditions
int calibrateMoisture(int rawValue, int dryValue, int wetValue)
{
  return map(rawValue, valueDry, valueWet, 0, 100);
  // manually : ((sensor_analog/1900.00) * 100);
}

