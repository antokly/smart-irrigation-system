/**
 * Actuators setup and processes
 */

#include "actuators.h"

void setupPump(void)
{
  pinMode(PUMP_PIN, OUTPUT);
}

void processPumpLogic(float value)
{
  int level = 0;

  if (value >= 1000) level = 100;
  else if (value >= 750) level = 75;
  else if (value >= 500) level = 50;
  else if (value >= 250) level = 25;
  else if (value >= 100) level = 10;
  else level = 0;

  switch (level) {
      case 100:
          Serial.println("Water Level: 100% - MAXIMUM");
          digitalWrite(PUMP_PIN, LOW);
          break;
      case 75:
          Serial.println("Water Level: 75%");
          break;
      case 50:
          Serial.println("Water Level: 50%");
          break;
      case 25:
          Serial.println("Water Level: 25%");
          break;
      case 10:
          Serial.println("Water Level: 10% - LOW");
          digitalWrite(PUMP_PIN, HIGH);
          break;
      case 0:
          Serial.println("Water Level: 0% - EMPTY");
          digitalWrite(PUMP_PIN, HIGH);
          break;
      default:
          Serial.println("Water Level: Unknown");
          break;
  }
}
