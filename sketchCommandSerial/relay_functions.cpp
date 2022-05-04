#include "generic_functions.h"
#include "relay_functions.h"
#include <neotimer.h>

#define MINTIME 1000l

#define MAXINPUT 2

Relay Relays[] = {4, 1000, false,
                  5, 1000, false,
                  6, 1000, false,
                  7, 1000, false,
                  8, 1000, false,
                  9, 1000, false
                 };

// 4 1- 12V - dose pump
// 5 2- 12V - dose pump
// 6 3- 12V - dose pump
// 7 4- 12V - solenoid valve
// 8 5- 24v - Main pump
// 9 6- 24v - N/A

Neotimer RelayTimers[RELAYS];

void debugRelayData() {
  for (int i = 0; i < RELAYS; i++) {
    Serial.print("#Relay: ");
    Serial.print(i);
    Serial.print("|Pin: ");
    Serial.print(Relays[i].pin);
    Serial.print("|Timer: ");
    Serial.println(Relays[i].maxTimer);
    Serial.print("|auto: ");
    Serial.println(Relays[i].automatic);
  }
}

void relayMain(String command, String input) {
  String inputs[MAXINPUT];
  int i = 0;

  while (getValue(input, '|', i) != NULL && i < MAXINPUT) {
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
  else if (command == "auto") {
    toggleAuto(inputs[0].toInt());
  }
  else {Serial.println("Invalid relay command");}
}

void enableRelay(int id) {
  if (id >= 0 && id < RELAYS && !RelayTimers[id].waiting()) {
    digitalWrite(Relays[id].pin, HIGH);
    RelayTimers[id] = Neotimer(Relays[id].maxTimer);
    RelayTimers[id].start();
    Serial.print("#Relay Enable :");
    Serial.println(id);
  }
}

void disableRelay(int id) {
  if (id >= 0 && id < RELAYS) {
    digitalWrite(Relays[id].pin, LOW);
    RelayTimers[id].reset();
    Serial.print("#Relay Disable :");
    Serial.println(id);
  }
}

void loopRelays() {
  for (int i = 0; i < RELAYS; i++) {
    if (RelayTimers[i].done()) {
      if (Relays[i].automatic) {
        RelayTimers[i].start();
        digitalWrite(Relays[i].pin, !digitalRead(Relays[i].pin));
        // invert current output 
      } else {
        disableRelay(i);
      }
    }
  }
}

void updateTimer (int id, long newTime) {
  if (id >= 0 && id < RELAYS && newTime >= MINTIME) {
    Relays[id].maxTimer = newTime;
    Serial.print("#Relay:");
    Serial.print(id);
    Serial.print("|Timer:");
    Serial.println(newTime);
    writeEEPROM();
  }
}

void toggleAuto(int id) {
  if (id >= 0 && id < RELAYS) {
    Relays[id].automatic = !Relays[id].automatic;
    Serial.print("#Relay:");
    Serial.print(id);
    Serial.print("|Auto:");
    Serial.println(Relays[id].automatic);
    writeEEPROM();
  }
}
