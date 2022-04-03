
const float  V_OFFSET = 0.483 ;

const int PSI_MAX = 150;
const int PSI_MIN = 0;
const float V_RANGE = 4; /*0.5v - 4.5v*/

#define PRES_PIN A3
float V, P;

void setup()
{
  Serial.begin(9600);
  Serial.println("/** Water pressure sensor demo **/");
}
void loop()
{
  V = analogRead(PRES_PIN) * 5.00 / 1024;     //Sensor output voltage
  P = (V - V_OFFSET) * PSI_MAX / V_RANGE;     //Calculate water pressure

  Serial.print("Voltage:");
  Serial.println(V, 3);

  Serial.print("Pressure:");
  Serial.print(P, 1);
  Serial.println(" PSI");

  delay(500);
}
