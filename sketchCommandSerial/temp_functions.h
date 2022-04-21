#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H
#include <Arduino.h>

#define TEMPS 1

struct TempSensor {
  int pin;
};

extern TempSensor TempSensors[TEMPS];

void debugTempData();
float getTemp();

#endif
