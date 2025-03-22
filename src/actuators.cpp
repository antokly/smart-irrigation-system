#include "actuators.h"

const int pump_pin = 26;

void pump_init(void)
{
  pinMode(pump_pin, OUTPUT);
}

void pump_irrigation(uint8_t moisture)
{
    if(moisture >= 60){
    
    Serial.println("Enough Water for plants");
    digitalWrite(pump_pin, LOW);
  
    }else if(moisture <= 5){

    Serial.println("Water Level Is Low");
    digitalWrite(pump_pin, HIGH);

    }else{

    Serial.println("Water Level Is OK");
    
  }
  delay(2000);
}