#ifndef EC_FUNCTIONS_H
#define EC_FUNCTIONS_H
#include <Arduino.h>

void setupEC();
String loopEC();
void sendECCommand(char* pCommand);
String getECSensor();

#endif
