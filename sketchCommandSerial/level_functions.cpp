#include "level_functions.h"


LevelSensor LevelSensors[] = {14};

int getLevel(int id){
  int level = digitalRead(LevelSensors[id].pin);
  //Serial.println(level);
  return level;
  }
