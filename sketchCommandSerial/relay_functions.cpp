#include "generic_functions.h"
#include "relay_functions.h"
#include <neotimer.h>

#define MINTIME 1000l

Relay Relays[] = {4, 1000,
                  5, 1000,
                  6, 1000,
                  7, 1000,
                  8, 1000,
                  9, 1000
                 };

// 4 - 12V - dose pump
// 5 - 12V - dose pump
// 6 - 12V - dose pump
// 7 - 12V - solenoid valve
// 8 - 24v - Main pump
// 9 - 24v - N/A

Neotimer RelayTimers[RELAYS];

void debugRelayData() {
  for (int j = 0; j < RELAYS; j++) {
    Serial.print("Relay: ");
    Serial.print(j);
    Serial.print("|Pin: ");
    Serial.print(Relays[j].pin);
    Serial.print("|Timer: ");
    Serial.println(Relays[j].maxTimer);
  }
}

void relayMain(String command, String input) {
  String input;
  String inputs[2];
  int i = 0;

  while (getValue(input, '|', i) != NULL) {
    inputs[i] = getValue(input, '|', i);
    i++;
  }

  if (command == "enable") {
    enableRelay(inputs[0].toInt());
  }
  else if (command == "disable") {
    disableRelay(inputs[0].toInt());
  }
  else if (command == "timer") {
    updateTimer(inputs[0].toInt(), atol(inputs[1].c_str()));
  }
}

void enableRelay(int id) {
  if (id >= 0 && id < RELAYS) {
    digitalWrite(Relays[id].pin, HIGH);
    RelayTimers[id] = Neotimer(Relays[id].maxTimer);
    RelayTimers[id].start();
    Serial.print("Relay Enable :");
    Serial.println(id);
  }
}

void disableRelay(int id) {
  if (id >= 0 && id < RELAYS) {
    digitalWrite(Relays[id].pin, LOW);
    RelayTimers[id].reset();
    Serial.print("Relay Disable :");
    Serial.println(id);
  }
}

void loopRelays() {
  for (int i = 0; i < RELAYS; i++) {
    if (RelayTimers[i].done()) {
      disableRelay(i);
    }
  }
}

void updateTimer (int id, long newTime) {
  if (id >= 0 && id < RELAYS && newTime >= MINTIME) {
    Relays[id].maxTimer = newTime;
    Serial.print("Relay:");
    Serial.print(id);
    Serial.print("|Timer:");
    Serial.println(newTime);
    writeEEPROM();
  }
}
