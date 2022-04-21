#include "ph_functions.h"
#include <DFRobot_PH.h>

PhSensor PhSensors[] = {A1};
DFRobot_PH phsen;
float voltage, phValue;

void setupPH() {
  phsen.begin();
}

void debugPhData() {
  for (int i = 0; i < PH; i++) {
    Serial.print("Ph: ");
    Serial.print(i);
    Serial.print("|Pin: ");
    Serial.print(PhSensors[i].pin);
  }
}

float getPh(float temperature) {
  voltage = analogRead(PhSensors[0].pin) / 1024.0 * 5000; // read the voltage
  phValue = phsen.readPH(voltage, temperature); // convert voltage to pH with temperature compensation

  return phValue;
}

void caliPh(float temperature, char* dataptr){
  voltage = analogRead(PhSensors[0].pin) / 1024.0 * 5000; // read the voltage
  phsen.calibration(voltage,temperature,dataptr);
  }
