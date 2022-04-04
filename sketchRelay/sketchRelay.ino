#include <neotimer.h>
int Relays = 6;
int RelayID2Pin[] = {4, 5, 6, 7, 8, 9};

// 4 - 12V - dose pump
// 5 - 12V - dose pump
// 6 - 12V - dose pump
// 7 - 12V - solenoid valve
// 8 - 24v - Main pump
// 9 - 24v - N/A

Neotimer RelayTimers[2];
const long RelayMaxEnable[] = {1000, 1000, 1000, 1000, 1000, 1000};

void enableRelay(int id) {
  digitalWrite(id, HIGH);
  RelayTimers[id] = Neotimer(RelayMaxEnable[id]);
  RelayTimers[id].start();
}

void disableRelay(int id) {
  digitalWrite(id, LOW);
}

void loopRelays() {
  for (int i = 0; i < Relays; i++) {
    if (RelayTimers[i].done()) {
      Serial.println("Relay auto stop");
      RelayTimers[i].reset();
    }
  }
}
