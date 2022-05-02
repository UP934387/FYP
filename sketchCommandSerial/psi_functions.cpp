#include "psi_functions.h"

PsiSensor PsiSensors[] = {A0, 150, 0, 4.0, 0.483};

const float vPinMax = 5.00;


void debugPSIData() {
  for (int i = 0; i < PRES; i++) {
    Serial.print("Pressure: ");
    Serial.print(i);
    Serial.print("|Pin: ");
    Serial.print(PsiSensors[i].pin);
    Serial.print("|PSImax: ");
    Serial.print(PsiSensors[i].PSImax);
    Serial.print("|PSImin: ");
    Serial.print(PsiSensors[i].PSImin);
    Serial.print("|vRange: ");
    Serial.print(PsiSensors[i].vRange);
    Serial.print("|vOffset: ");
    Serial.println(PsiSensors[i].vOffset);
  }
}

float getPSI() {
  float V, P;
  V = analogRead(PsiSensors[0].pin) * vPinMax / 1024;     //Sensor output voltage
  P = (V - PsiSensors[0].vOffset) * PsiSensors[0].PSImax / PsiSensors[0].vRange;     //Calculate water pressure

  return (P < PsiSensors[0].PSImin) ? PsiSensors[0].PSImin : P; // prevent psi reading below min value
}

void configSensor(int id, PsiSensor newPsiSensor ) {
  PsiSensors[id] = newPsiSensor;
}
