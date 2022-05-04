#include <OneWire.h>
#include "temp_functions.h"

TempSensor TempSensors[] = {15};
OneWire ds(TempSensors[0].pin);

void debugTempData() {
  for (int i = 0; i < TEMPS; i++) {
    Serial.print("#Temp: ");
    Serial.print(i);
    Serial.print("|Pin: ");
    Serial.println(TempSensors[i].pin);
  }
}

float getTemp() {
  byte data[12];
  byte addr[8];
  if (!ds.search(addr)) {
    //no sensors, reset search
    ds.reset_search();
    return -1000;
  }
  else if ( OneWire::crc8(addr, 7) != addr[7]) {
    //invalid address bad crc
    return -1000;
  }
  else if (addr[0] != 0x10 && addr[0] != 0x28) {
    //unknown device family code invalid
    return -1000;
  }

  ds.reset();
  ds.select(addr);
  // Command "Convert T" with parasitic power
  ds.write(0x44, 1);
  byte present = ds.reset();
  ds.select(addr);
  // Command "Read Scratchpad"
  ds.write(0xBE);

  for (int i = 0; i < 9; i++) { 
    //Scratchpad is 9 bytes
    data[i] = ds.read();
  }
  ds.reset_search();
  
  //result is 16 bit signed integer D0 LSB | D1 MSB
  int16_t raw = (data[1] << 8) | data[0]; 
  float temperature = (float)raw / 16.0;

  return temperature;
}
