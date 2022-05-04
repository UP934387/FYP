#ifndef PH_FUNCTIONS_H
#define PH_FUNCTIONS_H
#include <Arduino.h>

#define PH 1

struct PhSensor {
  byte pin;
};

extern PhSensor PhSensors[PH];

void debugPhData();
float getPh(float temperature);
void caliPh(float temperature, char* dataptr);

#endif
