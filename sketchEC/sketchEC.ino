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

void setup() {
  Serial.begin(38400);

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
