//test code for knock sensors
const byte interruptPin1 = 6;
const byte interruptPin2 = 7;
const byte interruptPin3 = 8;
void setup() {
  // put your setup code here, to run once:

  
    //intialize analog knock (bumper) sensor
    pinMode(interruptPin1, INPUT_PULLUP);
    pinMode(interruptPin2, INPUT_PULLUP);
    pinMode(interruptPin3, INPUT_PULLUP);
  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), knock, RISING); // pin, procedure, event(trigger)
  attachInterrupt(digitalPinToInterrupt(interruptPin2), knock, RISING); // pin, procedure, event(trigger)
  attachInterrupt(digitalPinToInterrupt(interruptPin3), knock, RISING); // pin, procedure, event(trigger)
}

void knock() {
  Serial.println("1");
  delay(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("0");
}
