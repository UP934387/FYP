#include "relay_functions.h"
#include "ec_functions.h"
#include "generic_functions.h"
#include "temp_functions.h"
#include "level_functions.h"
#include "psi_functions.h"
#include "ph_functions.h"

#define MAXINPUT 3

void setup() {
  Serial.begin(115200);
  setupEC();
  loadConfig();
}
// COMMAND FORMAT
// COMMAND
// COMMAND;DATA
// COMMAND;SUBCOMMAND;DATA

// DATA FORMAT
// DATA1
// DATA1|DATA2

float temp = 0, ph = 0, psi = 0;
int level = 0;
String ec = "";
void loop() {
  String input;
  String inputs[MAXINPUT];
  int i = 0;

  if (Serial.available())  {
    input = Serial.readStringUntil('\n');
    while (getValue(input, ';', i) != NULL && i < MAXINPUT) {
      // get word from string, until max size of array
      inputs[i] = getValue(input, ';', i);
      i++;
    }

    if (inputs[0] == "sensorsread") {
      displaySensors(temp, level, ph, ec, psi);
    }
    else if (inputs[0] == "relay") {
      relayMain(inputs[1], inputs[2]);
    }
    else if (inputs[0] == "ec") {
      int bufSize = inputs[1].length() + 1;
      char buf[bufSize];
      inputs[1].toCharArray(buf, bufSize);
      char* dataptr;
      dataptr = buf;
      // convert string to char array to be used with i2c -> uart lib
      sendECCommand(dataptr);
      ec = getECResponse();
      if (ec != "") {
        Serial.println(ec);
      }
    }
    else if (inputs[0] == "ph") {
      int bufSize = inputs[1].length() + 1;
      char buf[bufSize];
      inputs[1].toCharArray(buf, bufSize);
      char* dataptr;
      dataptr = buf;
      // convert string to char array to be used with ph sensor
      caliPh(temp, dataptr);
    }
    else if (inputs[0] == "readeeprom") {
      readEEPROM();
    }
    else if (inputs[0] == "writeeeprom") {
      writeEEPROM();
    }
    else if (inputs[0] == "dbg") {
      debugECData();
      debugRelayData();
      debugLevelData();
      debugPSIData();
      debugTempData();
      debugPhData();
    }
    else {
      Serial.println("Command Not Found");
    }
  }


  loopRelays();
  float temp2 = getTemp();
  temp = (temp2 == -1000) ? temp : temp2;
  level = getLevel(0);
  ph = getPh(temp);
  psi = getPSI();

  char buffer[4];
  snprintf(buffer, sizeof(buffer), "%f", temp);
  sendECCommand(buffer);
  ec = getECResponse();

  if (psi >= 90) {
    disableRelay(4);
    }
}
