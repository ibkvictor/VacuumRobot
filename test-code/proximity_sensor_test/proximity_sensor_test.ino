//test code for infra-red proximity sensors
#include <math.h>
#include <SharpIR.h>
int IRpin = A0;
SharpIR sensor(SharpIR::GP2Y0A21YK0F, IRpin);

void setup() {
    Serial.begin(9600);
}

void loop(){
  float distance = sensor.getDistance( false );
  Serial.println(distance);
}