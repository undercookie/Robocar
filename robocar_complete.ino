//defining all the pins that the motors are attached to:
#define MOTORS_LEFT_BACKWARD_PIN 6
#define MOTORS_LEFT_FORWARD_PIN 11
#define MOTORS_RIGHT_BACKWARD_PIN 3
#define MOTORS_RIGHT_FORWARD_PIN 5

char answer;
int pos = 0;

//the servo:
#include <Servo.h>
Servo myservo; 

//all the sensor stuff
#include <Wire.h>
#include <VL53L1X.h>
VL53L1X sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  pinMode(MOTORS_LEFT_BACKWARD_PIN, OUTPUT);
  pinMode(MOTORS_LEFT_FORWARD_PIN, OUTPUT);
  pinMode(MOTORS_RIGHT_BACKWARD_PIN, OUTPUT);
  pinMode(MOTORS_RIGHT_FORWARD_PIN, OUTPUT);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
  sensor.setTimeout(500);
  myservo.attach(9);
  myservo.write(pos);
}

void move_forward() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 200);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 200);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
}

void move_backward() {
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 200);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 200);
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 0);
}

void turn_left() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 120);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 200);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}

void turn_right() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 200);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 120);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}

void sharp_right() {
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 200);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 0);
}

void sharp_left() {
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 200);
}

void halt() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}

void turn_left_wallfollowing() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 0); 
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 128);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}

void turn_right_wallfollowing() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 128);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}

void sensormeasurement_wall_following() {
  //Long: 360cm; Medium: 290cm; Short: 136cm
  sensor.setDistanceMode(VL53L1X::Short);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);
  sensor.read();
  Serial.print(sensor.ranging_data.range_mm);
  
}

void servo_wallfollowing() {
  for (pos = 0; pos <= 45; pos += 1) { 
    // in steps of 1 degree
    myservo.write(pos);              
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
  answer = Serial.read();

  switch (answer)
  {
    case 'F':
    move_forward();
    break;

    case 'B':
    move_backward();
    break;

    case 'L':
    turn_left();
    break;

    case 'R':
    turn_right();
    break;

    case 'E':
    sharp_right();
    break;

    case 'Q':
    sharp_left();
    break;

    case 'H':
    halt();
    break;

    case 'X':
    sensormeasurement_wall_following();
    break;

    case 'T':
    turn_left_wallfollowing();
    break;

    case 'S':
    turn_right_wallfollowing();
    break;

    case 'V':
    servo_wallfollowing();
    break;

    default:
    break;
  }
}
}
