// COMMAND DOCUMENTATION
// L1     | Enable Debug LEDs
// L0     | Disable Debug LEDs
// R      | Single Reading Return
// TT.T   | Single Reading Return Temp Compensated
// TT.T,C | Continous Reading Return Temp Compensated
// C      | Continuous Reading Return
// E      | Stop Reading / Standby
// X      | Factory Reset
// I      | Device Info
// P1     | Set Sensor to K0.1
// P2     | Set Sensor to K1.0
// P3     | Set Sensor to K10.0
// Z0     | Dry Calibration
// Z2     | Calibration 220us (K0.1)
// Z30    | Calibration 3,000us (K0.1)
// Z10    | Calibration 10,500us (K1.0)
// Z40    | Calibration 40,000us (K1.0)
// Z62    | Calibration 62,000us (K10.0)
// Z90    | Calibration 90,000us (K10.0)

#include "ec_functions.h"
#include <DFRobot_IICSerial.h>

ECSensor ECSensors[] = {2, 3, 1, 1, SUBUART_CHANNEL_1};
// SDA = 2, SCL = 3, IA0 = 1, IA1 = 1, subUartChannel = SUBUART_CHANNEL_1

//Construct I2C -> UART1 object 
DFRobot_IICSerial iicSerial1(Wire, ECSensors[0].subUartChannel, 
                            ECSensors[0].IA1, ECSensors[0].IA0);

void debugECData() {
  for (int i = 0; i < ECS; i++) {
    Serial.print("#EC: ");
    Serial.print(i);
    Serial.print("|SDA: ");
    Serial.print(ECSensors[i].SDA);
    Serial.print("|SCL: ");
    Serial.print(ECSensors[i].SCL);
    Serial.print("|IA0: ");
    Serial.print(ECSensors[i].IA0);
    Serial.print("|IA1: ");
    Serial.print(ECSensors[i].IA1);
    Serial.print("|subUartChannel: ");
    Serial.println(ECSensors[i].subUartChannel);
  }
}

void setupEC() {
  // init UART1 at 38400 baud EC controller spec
  iicSerial1.begin(38400);
}

String getECResponse() {
  if (iicSerial1.available()) {
    return getECSensor();
  }
  return "000";
}

void sendECCommand(char* pCommand) {
  iicSerial1.print(pCommand);
  iicSerial1.print("\r");
  // all commands must end with a carriage return and a line feed
}

String getECSensor() {
  char c;
  String buf;
  char buf2[iicSerial1.available() + 1];
  while (iicSerial1.available()) {
    //Read data of UART1 receiver buffer
    c = iicSerial1.read();
    //Convert individual chars to whole String
    buf += c;
  }
  return buf;
}
