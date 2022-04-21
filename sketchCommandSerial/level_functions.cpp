#include "level_functions.h"


LevelSensor LevelSensors[] = {14};

void debugLevelData() {
  for (int i = 0; i < LEVELS; i++) {
    Serial.print("Level: ");
    Serial.print(i);
    Serial.print("|Pin: ");
    Serial.print(LevelSensors[i].pin);
  }
}


int getLevel(int id){
  int level = digitalRead(LevelSensors[id].pin);
  return level;
  }
