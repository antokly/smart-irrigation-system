#include <Arduino.h>
#include "sensors.h"
#include "actuators.h"
#include "network_base.h"
#include "SISconfig.h"
#include "mqtt_manager.h"

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
  //  Humidity Measuring
  uint8_t humidity = sensor_data_acquisition();
  String humidityStr = String(humidity);

  //  Send humidity data every 5 sec
  static unsigned long lastMsg = 0;
  unsigned long actualTs = millis();
  if (actualTs - lastMsg > 5000) {
    String message = "Hello, MQTT! New Data just Popped : " + humidityStr;
    mqtt_send_data("/test/topic", message.c_str()); // Convert String to C-string
    lastMsg = actualTs;
  }

  //  Irrigation
  pump_irrigation(humidity);

  delay(1000);
}