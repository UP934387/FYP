#include "relay_functions.h"
#include "ec_functions.h"
#include "generic_functions.h"
#include "temp_functions.h"
#include "level_functions.h"


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
  String input, command, data, extra;

  if (Serial.available())  {
    input = Serial.readStringUntil('\n');
    command = getValue(input, ';', 0);
    data = getValue(input, ';', 1);
    extra = getValue(input, ';', 2);

    if (command == "sensorsread") {

    }
    else if (command == "configrelay") {
      relayMain(data, extra);
    }
    else if (command == "configec") {
      char buf[data.length() + 1];
      data.toCharArray(buf, data.length() + 1);
      char* dataptr;
      dataptr = buf;
      sendECCommand(dataptr);
    }
    else if (command == "configph") {
      Serial.println(data);
    }
    else if (command == "configpsi") {
      Serial.println(data);
    }
    else if (command == "readeeprom") {
      readEEPROM();
    }
    else if (command == "dbg") {
      debugECData();
      debugRelayData();
    }
    else {
      Serial.println("Command Not Found");
    }
  }


  loopRelays();
  float temp = getTemp();
  int level = getLevel();
  String ec = loopEC();
  if (ec != "") {
    Serial.println(ec);
  }

}
