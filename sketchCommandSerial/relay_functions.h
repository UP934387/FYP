#ifndef RELAY_FUNCTIONS_H
#define RELAY_FUNCTIONS_H
#include <Arduino.h>

#define RELAYS 6

struct Relay {
  int pin;
  long maxTimer;
  bool automatic;
};

extern Relay Relays[RELAYS];

void debugRelayData();
void enableRelay(int id);
void disableRelay(int id);
void loopRelays();
void updateTimer (int id, long newTime);
void relayMain(String command, String input);
void toggleAuto(int id);

#endif
