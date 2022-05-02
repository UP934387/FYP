#ifndef GENERIC_FUNCTIONS_H
#define GENERIC_FUNCTIONS_H
#include <Arduino.h>
#include "relay_functions.h"
#include "ec_functions.h"
#include "temp_functions.h"
#include "level_functions.h"
#include "psi_functions.h"
#include "ph_functions.h"


struct EEPROMstructure {
  Relay EEPROM_Relays[RELAYS];
  ECSensor EEPROM_ECsensors[ECS];
  TempSensor EEPROM_TempSensors[TEMPS];
  LevelSensor EEPROM_LevelSensors[LEVELS];
  PsiSensor EEPROM_PsiSensors[PRES];
  PhSensor EEPROM_PhSensors[PH];
};

void writeEEPROM();
void readEEPROM();
void loadConfig();
void setupgpio();
void displaySensors(float temp, int level, float ph, String ec, float psi);
String getValue(String data, char separator, int index);

#endif
