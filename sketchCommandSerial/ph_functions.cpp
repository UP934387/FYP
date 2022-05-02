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
    Serial.println(PhSensors[i].pin);
  }
}

float getPh(float temperature) {
  // Read Voltage from Ph Sensor pin 
  voltage = analogRead(PhSensors[0].pin) / 1024.0 * 5000;
  // voltage & tempature converted by DFROBOT_PH Libary to Ph value
  phValue = phsen.readPH(voltage, temperature);

  return phValue;
}

void caliPh(float temperature, char* dataptr){
  // Read Voltage from Ph Sensor pin 
  voltage = analogRead(PhSensors[0].pin) / 1024.0 * 5000;
  // using voltage & tempature to caliebrate.
  // commands are enterph, calph, exitph
  phsen.calibration(voltage,temperature,dataptr);
  }
