#include "relay_functions.h"
#include "ec_functions.h"

void setup() {
  Serial.begin(115200);
  setupEC();
}

void loop() {
  String input, command, data;

  if (Serial.available())  {
    input = Serial.readStringUntil('\n');
    command = getValue(input, ';', 0);
    data = getValue(input, ';', 1);
  }
  if (command == "sensorsread") {

  }
  else if (command == "relayenable") {
    enableRelay(data.toInt());
  }
  else if (command == "relaydisable") {
    disableRelay(data.toInt());
  }
  else if (command == "configec") {
    char buf[data.length()+1];
    data.toCharArray(buf, data.length()+1);
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
  else if (command == "configtemp") {
    Serial.println(data);
  }
  else if (command == "configlevel") {

  }
  loopRelays();
  String ec = loopEC();
  if (ec != "") {
    Serial.println(ec);
  }

}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
