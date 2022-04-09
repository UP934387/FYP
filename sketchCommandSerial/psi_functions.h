#ifndef PSI_FUNCTIONS_H
#define PSI_FUNCTIONS_H
#include <Arduino.h>

#define PRES 1

struct PsiSensor {
  byte pin;
  int PSImax;
  int PSImin;
  float vRange;
  float vOffset;
};

extern PsiSensor PsiSensors[PRES];

float getPSI();

#endif
