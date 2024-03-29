#ifndef LEVEL_FUNCTIONS_H
#define LEVEL_FUNCTIONS_H
#include <Arduino.h>

#define LEVELS 1

struct LevelSensor {
  int pin;
};

extern LevelSensor LevelSensors[LEVELS];

void debugLevelData();
int getLevel(int id);

#endif
