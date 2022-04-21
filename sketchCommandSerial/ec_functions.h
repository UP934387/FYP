#ifndef EC_FUNCTIONS_H
#define EC_FUNCTIONS_H
#include <Arduino.h>

#define ECS 1

struct ECSensor {
  int SDA;
  int SCL;
  uint8_t IA0;
  uint8_t IA1;
  uint8_t subUartChannel;
};

extern ECSensor ECSensors[ECS];

void debugECData();
void setupEC();
String getECResponse();
void sendECCommand(char* pCommand);
String getECSensor();

#endif
