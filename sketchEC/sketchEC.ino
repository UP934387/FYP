#include <DFRobot_IICSerial.h>

DFRobot_IICSerial iicSerial1(Wire, /*subUartChannel =*/SUBUART_CHANNEL_1,/*IA1 = */1,/*IA0 = */1);//Construct UART1
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
// P,1    | Set Sensor to K0.1
// P,2    | Set Sensor to K1.0
// P,3    | Set Sensor to K10.0
// Z0     | Dry Calibration
// Z2     | Calibration 220us (K0.1)
// Z30    | Calibration 3,000us (K0.1)
// Z10    | Calibration 10,500us (K1.0)
// Z40    | Calibration 40,000us (K1.0)
// Z62    | Calibration 62,000us (K10.0)
// Z90    | Calibration 90,000us (K10.0)

void setup() {
  Serial.begin(38400); /*to host device serial (Pi/PC)*/

  iicSerial1.begin(/*baud = */38400);/*UART1 init*/
  sendECCommand((char*) "C"); /* send pointer to char array*/

}

void loop() {
  if (iicSerial1.available()) {
    char* ecData = getECSensor();
    Serial.println(ecData);
    free(ecData);
  }
}

void sendECCommand(char* pCommand) {
  iicSerial1.write(pCommand);
  iicSerial1.write("/r");
}


char* getECSensor() {
  char c;
  char* buf = (char*) malloc(100); /*alloc 100 bytes to return*/
  while (iicSerial1.available()) {
    c = iicSerial1.read();/*Read data of UART1 receive buffer */
    strcat(buf, &c);
  }
  return buf;
}
