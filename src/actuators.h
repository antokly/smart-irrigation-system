#ifndef DEF_ACTUATORS
#define DEF_ACTUATORS

#include "sensors.h"

void pump_init(void);
void pump_irrigation(uint8_t moisture);

#endif