
#ifndef DEF_SENSOR
#define DEF_SENSOR

#include <Arduino.h>

enum SensorType {
  SENSOR_NONE,
  SENSOR_MOISTURE,
  SENSOR_HUMIDITY,
  SENSOR_TEMPERATURE
};

class Sensor {

    public:

        Sensor(SensorType = SENSOR_NONE);
        
        float readSensorValue(void);

        int getPin(void) const;
        SensorType getType(void) const;
        int getReadFreq(void) const;
        int getSendFreq(void) const;
        int getLastReadTs(void) const;
        int getLastSendTs(void) const;
        int getSamplesNb(void) const;

        void setPin(int pin);
        void setType(SensorType sensor_type);
        void setReadFreq(int read_freq);
        void setSendFreq(int send_freq);
        void setLastSendTs(int send_ts);
        void setSamplesNb(int samples_nb);

    private:

        int sensor_pin_ = 0;
        SensorType	sensor_type_ = SENSOR_NONE;
        int sensor_read_freq_ = 3000;
        int sensor_send_freq_ = 6000;
        unsigned long sensor_last_read_ts_ = 0;
        unsigned long sensor_last_send_ts_ = 0;
        int sensor_samples_nb_ = 25;
        // samples number by measure for moving average => Reduce noise on measures (" moyennage glissant ")   

        float readMoisture(int sensor_pin, int samples_nb);
        float readHumidity(int sensor_pin, int samples_nb);
        float readTemperature(int sensor_pin, int samples_nb);
        float filter(float raw_value);
        float calibrateMoisture(int raw_value, int dry_value, int wet_value);
};

float filterEMA(float new_value, float last_value, float alpha);


#endif