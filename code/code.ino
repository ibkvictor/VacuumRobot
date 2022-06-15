#include <math.h> 
#include <SharpIR.h>

// motors
//left wheel motor
int l_wheel_motor1 = 5;
int l_wheel_motor2 = 4;

//right wheeel motor
int r_wheel_motor1 = 2;
int r_wheel_motor2 = 3;

// vacuum motor: connected via irf520 mosfet
int vacuum_motor = 10;

// sensors
// infra-red distance sensor objects
SharpIR front(SharpIR::GP2Y0A21YK0F, A0);
SharpIR left(SharpIR::GP2Y0A21YK0F, A1);
SharpIR right(SharpIR::GP2Y0A21YK0F, A2);


//interrupt pin for ky-031  knock sensor
const byte bumper1 = 6;
const byte bumper2 = 7;
const byte bumper3 = 8;
const byte bumper4 = 9;

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

    // //initialize infra-red distance sensor
    // pinMode(front, INPUT); //front sensor
    // pinMode(right, INPUT); //right sensor
    // pinMode(left, INPUT); //left sensor

    //intialize analog knock (bumper) sensor
    pinMode(bumper1, INPUT_PULLUP);
    pinMode(bumper2, INPUT_PULLUP);
    pinMode(bumper3, INPUT_PULLUP);
    pinMode(bumper4, INPUT_PULLUP);

    //interrupt for bumper sensor
    attachInterrupt(digitalPinToInterrupt(bumper1), moveAway, RISING); //on rising edge of knock signal
    attachInterrupt(digitalPinToInterrupt(bumper2), moveAway, RISING);
    attachInterrupt(digitalPinToInterrupt(bumper3), moveAway, RISING);
    attachInterrupt(digitalPinToInterrupt(bumper4), moveAway, RISING);

    //start vacuuming
    digitalWrite(vacuum_motor, HIGH);
}

// does interrupt continue after procedure is done
void moveAway(){
    bool left_blocked = blocked(left);
    bool right_blocked = blocked(right);
    bool front_blocked = blocked(front);
    if(left_blocked && right_blocked && front_blocked){
        stop(100);
        moveBackward(100);
        moveRight(1000); // turn around
        Serial.print("  Turn AROUND ");
    }
    else if(right_blocked && left_blocked){
        stop(100);
        moveForward(1000); //  continue forward
        Serial.print("  continue forward ");
    }
    else if(right_blocked && front_blocked){
        stop(100);
        moveBackward(100);
        moveLeft(500); //  turn left
        Serial.print("  turn left ");
    }
    else if(left_blocked && front_blocked){
        stop(100);
        moveBackward(100);
        moveRight(500); //  turn right
        Serial.print("  turn right ");
    }
    else if(front_blocked){
        stop(100);
        moveBackward(100);
        moveRight(500); //  turn right
        Serial.print("  turn right ");
    }
    else if(right_blocked){
        stop(100);
        moveLeft(500); // turn left
        Serial.print("  turn left ");
    }
    else if(left_blocked){
        stop(100);
        moveRight(500); //  turn right
        Serial.print("  turn right ");
    }
    else{
        moveForward(1000);
        Serial.print("  continue forward ");
    }
}

// sharp distance sensor
double distance(int sensor){
    //returns sensor analog signal in distance
    //formula for SHARP GP2Y0A21YK0F
    return 29.988 * (pow(analogRead(sensor), -1.173));
}

// conditionals
bool blocked(SharpIR direction){
    if (direction.getDistance( false ) <= 10){
        return true;
    }
    return false;
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
    //compute blocking conditions at beginning of each loop
    bool left_blocked = blocked(left);
    bool right_blocked = blocked(right);
    bool front_blocked = blocked(front);
    if(left_blocked && right_blocked && front_blocked){
        stop(100);
        moveBackward(100);
        moveRight(1000); // turn around
        Serial.print("  Turn AROUND ");
    }
    else if(right_blocked && left_blocked){
        stop(100);
        moveForward(1000); //  continue forward
        Serial.print("  continue forward ");
    }
    else if(right_blocked && front_blocked){
        stop(100);
        moveBackward(100);
        moveLeft(500); //  turn left
        Serial.print("  turn left ");
    }
    else if(left_blocked && front_blocked){
        stop(100);
        moveBackward(100);
        moveRight(500); //  turn right
        Serial.print("  turn right ");
    }
    else if(front_blocked){
        stop(100);
        moveBackward(100);
        moveRight(500); //  turn right
        Serial.print("  turn right ");
    }
    else if(right_blocked){
        stop(100);
        moveLeft(500); // turn left
        Serial.print("  turn left ");
    }
    else if(left_blocked){
        stop(100);
        moveRight(500); //  turn right
        Serial.print("  turn right ");
    }
    else{
        moveForward(1000);
        Serial.print("  continue forward ");
    }
}