//test code for infra-red proximity sensors
#include <math.h>
#include <SharpIR.h>
int front = A2;
int left = A1;
int right = A0;
SharpIR f_sensor(SharpIR::GP2Y0A21YK0F, front);
SharpIR r_sensor(SharpIR::GP2Y0A21YK0F, right);
SharpIR l_sensor(SharpIR::GP2Y0A21YK0F, left);

void setup() {
    Serial.begin(9600);
}

void loop(){
  float f_distance = f_sensor.getDistance( true );
  float r_distance = r_sensor.getDistance( true );
  float l_distance = l_sensor.getDistance( true );

  Serial.println("f_distance");
  Serial.print(f_distance);
  Serial.println("l_distance");
  Serial.print(l_distance);
  Serial.println("r_distance");
  Serial.print(r_distance);
}
