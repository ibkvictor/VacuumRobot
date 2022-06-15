//test code for knock sensors
const byte interruptPin = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interruptPin), knock, RISING); // pin, procedure, event(trigger)
}

void knock() {
  Serial.println("1");
  delay(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("0");
}
