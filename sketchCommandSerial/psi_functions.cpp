#include "psi_functions.h"

PsiSensor PsiSensors[] = {A3, 150, 0, 4.0, 0.483};

const float vPinMax = 5.00;

float getPSI(int id) {
  float V, P;
  V = analogRead(PsiSensors[id].pin) * vPinMax / 1024;     //Sensor output voltage
  P = (V - PsiSensors[id].vOffset) * PsiSensors[id].PSImax / PsiSensors[id].vRange;     //Calculate water pressure

  return P;
}

void configSensor(int id, PsiSensor newPsiSensor ){
  PsiSensors[id] = newPsiSensor;
  }
