#include "relay_functions.h"
#include "ec_functions.h"
#include "generic_functions.h"
#include "temp_functions.h"
#include "level_functions.h"
#include "psi_functions.h"


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


void loop() {
  String input;
  String inputs[3];
  int i = 0;

  if (Serial.available())  {
    input = Serial.readStringUntil('\n');
    while(getValue(input, ';', i) != NULL) {
      inputs[i] = getValue(input, ';', i);
      i++;
      }
      
    if (inputs[0] == "sensorsread") {

    }
    else if (inputs[0] == "configrelay") {
      relayMain(inputs[1], inputs[2]);
    }
    else if (inputs[0] == "configec") {
      int bufSize = inputs[1].length() + 1;
      char buf[bufSize];
      inputs[1].toCharArray(buf, bufSize);
      char* dataptr;
      dataptr = buf;
      sendECCommand(dataptr);
    }
    else if (inputs[0] == "configph") {
      Serial.println(inputs[1]);
    }
    else if (inputs[0] == "configpsi") {
      Serial.println(inputs[1]);
    }
    else if (inputs[0] == "readeeprom") {
      readEEPROM();
    }
    else if (inputs[0] == "dbg") {
      debugECData();
      debugRelayData();
    }
    else {
      Serial.println("Command Not Found");
    }
  }


  loopRelays();
  float temp = getTemp(0);
  int level = getLevel(0);
  String ec = loopEC();
  if (ec != "") {
    Serial.println(ec);
  }

}
