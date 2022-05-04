#include "psi_functions.h"

PsiSensor PsiSensors[] = {A0, 150, 0, 4.0, 0.483};
const float vPinMax = 5.00;

void debugPSIData() {
  for (int i = 0; i < PRES; i++) {
    Serial.print("#Pressure: ");
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
  float voltage, pressure, voltage_compensated, v_p_step;
  //Sensor output voltage
  voltage = analogRead(PsiSensors[0].pin) * vPinMax / 1024;
  //sensor no pressure voltage is offset. remove offset from current voltage
  voltage_compensated = (voltage - PsiSensors[0].vOffset);
  //create voltage/pressure step size based of the voltage range and max psi
  v_p_step = PsiSensors[0].PSImax / PsiSensors[0].vRange;
  //multiply compensated voltage by the voltage/pressure step size
  pressure = voltage_compensated * v_p_step;

  // prevent psi reading below min value, clamp to min psi value
  return (pressure < PsiSensors[0].PSImin) ? PsiSensors[0].PSImin : pressure;
}
