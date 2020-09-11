//defining all the pins that the motors are attached to:
#define MOTORS_LEFT_BACKWARD_PIN 6
#define MOTORS_LEFT_FORWARD_PIN 11
#define MOTORS_RIGHT_BACKWARD_PIN 3
#define MOTORS_RIGHT_FORWARD_PIN 5

//all the sensor stuff:
#include <Wire.h>
#include <VL53L1X.h>
VL53L1X sensor;

//the servo:
#include <Servo.h>
Servo myservo; 

//extra variables and such stuff:
char answer;
int pos = 0;
int measure_right;
int measure_straight;
int measure_left;
int state = 0;
int timeCounter = 0;
VL53L1X distanceSensor;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
  sensor.setTimeout(50000);
  pinMode(MOTORS_LEFT_BACKWARD_PIN, OUTPUT);
  pinMode(MOTORS_LEFT_FORWARD_PIN, OUTPUT);
  pinMode(MOTORS_RIGHT_BACKWARD_PIN, OUTPUT);
  pinMode(MOTORS_RIGHT_FORWARD_PIN, OUTPUT);
  myservo.attach(9);
  myservo.write(pos);

}

void move_forward() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 128);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 128);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
}

void turn_slightly_left() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 150);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
    delay(100);
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}

void turn_slightly_right() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 100);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
    delay(100);
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}

void halt() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}


void servo_right_straight() {
  for (pos = 0; pos <= 60; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void servo_straight_left() {
  for (pos = 60; pos <= 120; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void servo_left_straight() {
  for (pos = 120; pos >= 60; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void servo_straight_right() {
  for (pos = 60; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void servo_stay() {
  if (pos = 60; pos == 60) {
    //delay(1000);
    
  }
}

void sensormeasurement_right() {
  //Long: 360cm; Medium: 290cm; Short: 136cm
  sensor.setDistanceMode(VL53L1X::Long); 
  sensor.setMeasurementTimingBudget(50);
  sensor.startContinuous(1000);
  sensor.read();
  Serial.print(3);
  Serial.print(sensor.ranging_data.range_mm);
}

void sensormeasurement_straight() {
  //Long: 360cm; Medium: 290cm; Short: 136cm
  sensor.setDistanceMode(VL53L1X::Long); 
  sensor.setMeasurementTimingBudget(50);
  sensor.startContinuous(1000);
  sensor.read();
  Serial.print(2);
  Serial.print(sensor.ranging_data.range_mm);
}

void sensormeasurement_left() {
  //Long: 360cm; Medium: 290cm; Short: 136cm
  sensor.setDistanceMode(VL53L1X::Long); 
  sensor.setMeasurementTimingBudget(50);
  sensor.startContinuous(1000);
  sensor.read();
  Serial.print(1);
  Serial.print(sensor.ranging_data.range_mm);
}

void statemachine() {
  if ((state == 0) && (timeCounter >= 100)) {
    servo_right_straight();
    sensormeasurement_straight();
    state == 1;
  }
  else if ((state == 1) && (timeCounter >= 200)) {
    servo_straight_left();
    sensormeasurement_left();
    state == 2;
  }
  else if ((state == 2) && (timeCounter >= 300)) {
    servo_left_straight();
    sensormeasurement_straight();
    state == 3;
  }
  else if ((state == 3) && (timeCounter >= 400)) {
    servo_straight_right();
    sensormeasurement_right();
    state == 0;
    timeCounter == 0;
  }
  timeCounter++;
}

void loop() {

  statemachine();
  
  if (Serial.available() > 0) {
  
  answer = Serial.read();

  switch (answer)
  {
   case 'H':
   halt();
   //myservo.detach();
   break;

   case 'F':
   move_forward();
   break;

   case 'N':
   //move right
   turn_slightly_right();
   break;

   case 'M':
   //move left
   turn_slightly_left();
   break;

   default:
   break;
   }
  }
  delay(10);
}
