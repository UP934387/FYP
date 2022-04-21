#include <EEPROM.h>
#include "generic_functions.h"

byte EEPROMINIT = 104;
// used to check if EEPROM has valid config. change if EEPROM Struct changes

void writeEEPROM() {
  Serial.println("EEPROM WROTE");
  EEPROMstructure writeEEPROM;

  for (int i = 0; i < RELAYS; i++) {
    writeEEPROM.EEPROM_Relays[i] = Relays[i];
  };
  for (int j = 0; j < ECS; j++) {
    writeEEPROM.EEPROM_ECsensors[j] = ECSensors[j];
  };
  for (int k = 0; k < TEMPS; k++) {
    writeEEPROM.EEPROM_TempSensors[k] = TempSensors[k];
  };
  for (int l = 0; l < LEVELS; l++) {
    writeEEPROM.EEPROM_LevelSensors[l] = LevelSensors[l];
  };
  for (int m = 0; m < PRES; m++) {
    writeEEPROM.EEPROM_PsiSensors[m] = PsiSensors[m];
  };
  for (int n = 0; m < PH; n++) {
    writeEEPROM.EEPROM_PhSensors[n] = PhSensors[n];
  };
  EEPROM.put(0, EEPROMINIT);
  EEPROM.put(1, writeEEPROM);
}


void readEEPROM() {
  Serial.println("EEPROM READ");
  EEPROMstructure readEEPROM;

  EEPROM.get(1, readEEPROM);

  for (int i = 0; i < RELAYS; i++) {
    Relays[i] = readEEPROM.EEPROM_Relays[i];
  };
  for (int j = 0; j < ECS; j++) {
    ECSensors[j] = readEEPROM.EEPROM_ECsensors[j];
  };
  for (int k = 0; k < TEMPS; k++) {
    TempSensors[k] = readEEPROM.EEPROM_TempSensors[k];
  };
  for (int l = 0; l < LEVELS; l++) {
    LevelSensors[l] = readEEPROM.EEPROM_LevelSensors[l];
  };
  for (int m = 0; m < PRES; m++) {
    PsiSensors[m] = readEEPROM.EEPROM_PsiSensors[m];
  };
  for (int n = 0; m < PRES; n++) {
    PhSensors[n] = readEEPROM.EEPROM_PhSensors[n];
  };
}

void loadConfig() {
  byte key;
  EEPROM.get(0, key);
  if (key == EEPROMINIT) {
    Serial.println("Valid Config Detected");
    readEEPROM();
  }
  else {
    Serial.println("No Config Detected");
    writeEEPROM();
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
