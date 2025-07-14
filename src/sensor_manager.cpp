#include "sensor_manager.h"

const uint32_t valueDry = 0;
const uint32_t valueWet = 0;

// For EMA filter
static float value_filtered = 0;
const float alpha = 0.1;           // EMA smoothing factor: lower = smoother, but slower response

// Sensor Constructor
Sensor::Sensor(SensorType sensor_type)
{
  sensor_type_ = sensor_type;

  switch(sensor_type) {
    case SENSOR_NONE:
      break;
    case SENSOR_MOISTURE:
      sensor_pin_ = 35;
      sensor_read_freq_ = 3000;
      sensor_send_freq_ = 6000;
      sensor_samples_nb_ = 25;
      pinMode(sensor_pin_, INPUT);
      break;
    case SENSOR_HUMIDITY:
      sensor_pin_ = 34;
      pinMode(sensor_pin_, INPUT);
      sensor_read_freq_ = 3000;
      sensor_send_freq_ = 6000;
      sensor_samples_nb_ = 25;
      break;
    case SENSOR_TEMPERATURE:
      sensor_pin_ = 32;
      pinMode(sensor_pin_, INPUT);
      sensor_read_freq_ = 3000;
      sensor_send_freq_ = 6000;
      sensor_samples_nb_ = 25;
      break;
  }
}

float Sensor::readSensorValue(void)
{
  float  value = -1;
  float raw_avg_value = -1;

  switch(sensor_type_) {
    case SENSOR_NONE:
      Serial.println("No Sensor Detected");
      break;
    case SENSOR_MOISTURE:
      raw_avg_value = readMoisture(getPin(), getSamplesNb());
      value = filter(raw_avg_value);
      break;
    case SENSOR_HUMIDITY:
      value = readHumidity(getPin(), getSamplesNb());
      // value = filter(raw_avg_value);
      break;
    case SENSOR_TEMPERATURE:
      value = readTemperature(getPin(), getSamplesNb());
      // value = filter(raw_avg_value);
      break;
  }

  sensor_last_read_ts_ = millis();

  return value;
}

// Raw sensor data reading (mean of analog samples)
float Sensor::readMoisture(int sensor_pin, int samples_nb)
{
  //digitalWrite(sensor_vcc_pin, HIGH);
  //delay(100); // Wait for stabilization

  float sum = 0;
  for (int i = 0; i < samples_nb; ++i) {
    sum += analogRead(sensor_pin);
    delay(10);
  }

  //digitalWrite(sensor_vcc_pin, LOW);
  return sum / samples_nb;
}

// Apply filtering
float Sensor::filter(float raw_value)
{
  static bool first_reading = true;
  if (first_reading) {
    value_filtered = raw_value;
    first_reading = false;
  } else {
    value_filtered = filterEMA(raw_value, value_filtered, alpha);
  }
  return value_filtered;
}

// Exponential Moving Average filter
float filterEMA(float newValue, float lastValue, float alpha)
{
  return alpha * newValue + (1.0 - alpha) * lastValue;
}

// Map to meaning (optionally apply calibration)
// Calibrates raw sensor value to a percentage (0% = dry, 100% = wet)
// Requires prior measurement of raw values in dry and wet conditions
float Sensor::calibrateMoisture(int rawValue, int dryValue, int wetValue) 
{
  return map(rawValue, valueDry, valueWet, 0, 100);
  // manually : ((sensor_analog/1900.00) * 100);
}

float Sensor::readHumidity(int sensor_pin, int samples_nb)
{

  delay(100); // Wait for stabilization

  float sum = 0;
  for (int i = 0; i < samples_nb; ++i) {
    sum += analogRead(sensor_pin);
    delay(10);
  }

  return sum / samples_nb;
}

float Sensor::readTemperature(int sensor_pin, int samples_nb)
{

  float sum = 0;
  for (int i = 0; i < samples_nb; ++i) {
    sum += analogRead(sensor_pin);
    delay(10);
  }

  return sum / samples_nb;
}

int Sensor::getPin(void) const {
  return sensor_pin_;
}

int Sensor::getReadFreq(void) const {
  return sensor_read_freq_;
}

int Sensor::getSendFreq(void) const {
  return sensor_send_freq_;
}

int Sensor::getLastReadTs(void) const {
  return sensor_last_read_ts_;
}

int Sensor::getLastSendTs(void) const {
  return sensor_last_send_ts_;
}

int Sensor::getSamplesNb(void) const {
  return sensor_samples_nb_;
}

SensorType Sensor::getType(void) const {
  return sensor_type_;
}

void Sensor::setPin(int pin)
{
  sensor_pin_ = pin;
  return;
}

void Sensor::setType(SensorType sensor_type)
{
  sensor_type_ = sensor_type;
  return;
}

void Sensor::setReadFreq(int read_freq)
{
  sensor_read_freq_ = read_freq;
  return;
}

void Sensor::setSendFreq(int send_freq)
{
  sensor_send_freq_ = send_freq;
}

void Sensor::setLastSendTs(int send_ts)
{
  sensor_last_send_ts_ = send_ts;
}

void Sensor::setSamplesNb(int samples_nb)
{
  sensor_samples_nb_ = samples_nb;
  return;
}