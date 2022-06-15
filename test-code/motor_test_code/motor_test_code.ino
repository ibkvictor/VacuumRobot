// motors
//left wheel motor
int l_wheel_motor1 = 5;
int l_wheel_motor2 = 4;

//right wheeel motor
int r_wheel_motor1 = 2;
int r_wheel_motor2 = 3;

// vacuum motor: connected via irf520 mosfet
int vacuum_motor = 10;

//const pulse width modulator
const int PWMmin = 140; // 0 - 255  representing 0 - max volts

void setup(){
    //transmit feedback signal over serial monitor at 9600 baud rate
    Serial.begin(9600);

    //initialize digital pins of the motors
    pinMode(l_wheel_motor1, OUTPUT);
    pinMode(l_wheel_motor2, OUTPUT);
    pinMode(r_wheel_motor1, OUTPUT);
    pinMode(r_wheel_motor2, OUTPUT);

    //initialize digital pins of vacuum motor
    pinMode(vacuum_motor, OUTPUT);
    
    //start vacuuming
    digitalWrite(vacuum_motor, HIGH);
}
// stop
void stop(int move_time){
    analogWrite(l_wheel_motor1, 0);
    analogWrite(l_wheel_motor2, 0);
    analogWrite(r_wheel_motor1, 0);
    analogWrite(r_wheel_motor2, 0);
    delay(move_time);
}

// move_left
void moveLeft(int move_time){
    analogWrite(l_wheel_motor1, PWMmin);
    analogWrite(l_wheel_motor2, 0);
    analogWrite(r_wheel_motor1, 0);
    analogWrite(r_wheel_motor2, PWMmin);
    delay(move_time);
}

// move_right
void moveRight(int move_time){
    analogWrite(l_wheel_motor1, 0);
    analogWrite(l_wheel_motor2, PWMmin);
    analogWrite(r_wheel_motor1, PWMmin);
    analogWrite(r_wheel_motor2, 0);
    delay(move_time);
}

// move_forward
void moveForward(int move_time){
    analogWrite(l_wheel_motor1, PWMmin);
    analogWrite(l_wheel_motor2, 0);
    analogWrite(r_wheel_motor1, PWMmin);
    analogWrite(r_wheel_motor2, 0);
    delay(move_time);
}

// move_backwards
void moveBackward(int move_time){
    analogWrite(l_wheel_motor1, 0);
    analogWrite(l_wheel_motor2, PWMmin);
    analogWrite(r_wheel_motor1, PWMmin);
    analogWrite(r_wheel_motor2, 0);
    delay(move_time);
}

void loop(){
    moveForward(500);
    stop(100);
    Serial.print(" Move Forward ");
    moveBackward(100);
    stop(100);
    Serial.print(" Move Backward ");
    moveLeft(500);
    stop(100);
    Serial.print("  Turn Left ");
    moveRight(500);
    stop(100);
    Serial.print("  Turn Right ");
    moveRight(1000); // turn around
    stop(100);
    Serial.print("  Turn AROUND ");
}
