#include <EEPROM.h>
#include "generic_functions.h"

byte EEPROMINIT = 107;
// used to check if EEPROM has valid config. 
//change if EEPROM Struct changes
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

String getValue(String data, char separator, int index) {

  int found = 0;
  String foundWord = "";

  for (int i = 0; i <= data.length(); i++) {
    // loop over characters in String to max length
    if (data[i] == separator) {
      // increment found counter if separator
      found++;
    }
    else if (found == index) {
      // concatenate current char if found counter == index
      foundWord.concat(data[i]);
    }
    else if (found > index) {
      // break out of loop if found another separator
      break;
    }
  }
  // return the found word
  return foundWord;
}
