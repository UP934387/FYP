#include "ec_functions.h"
#include <DFRobot_IICSerial.h>

ECSensor ECSensors[] = {2, 3, 1, 1, SUBUART_CHANNEL_1};
// SDA = 2, SCL = 3, IA0 = 1, IA1 = 1, subUartChannel = SUBUART_CHANNEL_1

DFRobot_IICSerial iicSerial1(Wire, ECSensors[0].subUartChannel, ECSensors[0].IA1, ECSensors[0].IA0); //Construct UART1
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

void debugECData() {
  for (int j = 0; j < ECS; j++) {
    Serial.print("EC: ");
    Serial.print(j);
    Serial.print("|SDA: ");
    Serial.print(ECSensors[j].SDA);
    Serial.print("|SCL: ");
    Serial.print(ECSensors[j].SCL);
    Serial.print("|IA0: ");
    Serial.print(ECSensors[j].IA0);
    Serial.print("|IA1: ");
    Serial.print(ECSensors[j].IA1);
    Serial.print("|subUartChannel: ");
    Serial.println(ECSensors[j].subUartChannel);
  }
}


void setupEC() {
  iicSerial1.begin(38400);/*UART1 init*/
}

String loopEC() {
  if (iicSerial1.available()) {
    String ecData = getECSensor();
    return ecData;
  }
  return "";
}

void sendECCommand(char* pCommand) {
  iicSerial1.print(pCommand);
  iicSerial1.print("\r");
}

String getECSensor() {
  char c;
  String buf;
  char buf2[iicSerial1.available() + 1];
  while (iicSerial1.available()) {
    c = iicSerial1.read();/*Read data of UART1 receive buffer */
    buf += c;
  }
  return buf;
}
