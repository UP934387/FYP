#include "level_functions.h"


LevelSensor LevelSensors[] = {14};

int getLevel(){
  int level = digitalRead(LevelSensors[0].pin);
  //Serial.println(level);
  return level;
  }
