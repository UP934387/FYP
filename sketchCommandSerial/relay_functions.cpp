#include "relay_functions.h"
#include <neotimer.h>

#define RELAYS 6

long RelayMaxEnable[RELAYS] = {10000, 10000, 10000, 10000, 10000, 10000};
int RelayID2Pin[RELAYS] = {4, 5, 6, 7, 8, 9};

// 4 - 12V - dose pump
// 5 - 12V - dose pump
// 6 - 12V - dose pump
// 7 - 12V - solenoid valve
// 8 - 24v - Main pump
// 9 - 24v - N/A

Neotimer RelayTimers[RELAYS];

void enableRelay(int id) {
  //Serial.print(id);
  //Serial.println("Enable");
  if (id >= 0 && id < RELAYS) {
    digitalWrite(RelayID2Pin[id], HIGH);
    RelayTimers[id] = Neotimer(RelayMaxEnable[id]);
    RelayTimers[id].start();
    Serial.println("Relay Enable");
  }
}

void disableRelay(int id) {
  //Serial.print(id);
  //Serial.println("Disable");
  if (id >= 0 && id < RELAYS) {
    digitalWrite(RelayID2Pin[id], LOW);
    RelayTimers[id].reset();
    Serial.println("Relay Disable");
  }
}

void loopRelays() {
  for (int i = 0; i < RELAYS; i++) {
    if (RelayTimers[i].done()) {
      disableRelay(i);
      //Serial.print(i);
      Serial.println("Relay auto stop");
    }
  }
}
