#include <EEPROM.h>
#include "generic_functions.h"

byte EEPROMINIT = 104;
// used to check if EEPROM has valid config. change if EEPROM Struct changes

void writeEEPROM() {
  Serial.println("#EEPROM WROTE");
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
  for (int n = 0; n < PH; n++) {
    writeEEPROM.EEPROM_PhSensors[n] = PhSensors[n];
  };
  EEPROM.put(0, EEPROMINIT);
  EEPROM.put(1, writeEEPROM);
}


void readEEPROM() {
  Serial.println("#EEPROM READ");
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
  for (int n = 0; n < PRES; n++) {
    PhSensors[n] = readEEPROM.EEPROM_PhSensors[n];
  };
}

void setupgpio() {
  for (int i = 0; i < RELAYS; i++) {
    pinMode(Relays[i].pin, OUTPUT);
  };
  for (int k = 0; k < TEMPS; k++) {
    pinMode(TempSensors[k].pin, INPUT);
  };
  for (int l = 0; l < LEVELS; l++) {
    pinMode(LevelSensors[l].pin, INPUT);
  };
}

void displaySensors(float temp, int level, float ph, String ec, float psi) {
  Serial.print("Temp:");
  Serial.print(temp);
  Serial.print("|Level:");
  Serial.print(level);
  Serial.print("|Ph:");
  Serial.print(ph);
  Serial.print("|Ec:");
  Serial.print(ec);
  Serial.print("|PSI:");
  Serial.println(psi);
}

void loadConfig() {
  byte key;
  EEPROM.get(0, key);
  if (key == EEPROMINIT) {
    Serial.println("#Valid Config Detected");
    readEEPROM();
    setupgpio();
  }
  else {
    Serial.println("#No Config Detected");
    writeEEPROM();
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  // start (0) to end (-1) of String
  int seperatorIndex[] = {0, -1};
  int limit = data.length() - 1;

  for (int i = 0; i <= limit && found <= index; i++) {
    // loop until limit and have found the index of word requested
    if (data.charAt(i) == separator || i == limit) {
      // found seperator in String. or reached end of String
      // increment number of found words
      found++;
      // update index of seperator 0 (start)
      seperatorIndex[0] = seperatorIndex[1] + 1;
      // update index of seperator 1 to loop index (end)
      seperatorIndex[1] = (i == limit) ? i + 1 : i;
    }
  }
  // return if the word between seperators if found
  return found > index ? data.substring(seperatorIndex[0], seperatorIndex[1]) : "";
}
