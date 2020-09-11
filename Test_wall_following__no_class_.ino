#define MOTORS_LEFT_BACKWARD_PIN 6
#define MOTORS_LEFT_FORWARD_PIN 11
#define MOTORS_RIGHT_BACKWARD_PIN 3
#define MOTORS_RIGHT_FORWARD_PIN 5
char answer;

#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

void setup()
{
  pinMode(MOTORS_LEFT_BACKWARD_PIN, OUTPUT);
  pinMode(MOTORS_LEFT_FORWARD_PIN, OUTPUT);
  pinMode(MOTORS_RIGHT_BACKWARD_PIN, OUTPUT);
  pinMode(MOTORS_RIGHT_FORWARD_PIN, OUTPUT);
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); 
  sensor.setTimeout(500);
}

void move_forward() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 128);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 128);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
}

void turn_slightly_left() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 0); //maybe 50
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 128);
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}

void turn_slightly_right() {
    analogWrite(MOTORS_LEFT_FORWARD_PIN, 128);
    analogWrite(MOTORS_LEFT_BACKWARD_PIN, 0);
    analogWrite(MOTORS_RIGHT_FORWARD_PIN, 0); //maybe 50
    analogWrite(MOTORS_RIGHT_BACKWARD_PIN, 0);
}

void sensormeasurement() {
  sensor.setDistanceMode(VL53L1X::Short); 
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);
  sensor.read();
  Serial.print(sensor.ranging_data.range_mm); 
}

void loop() {
  sensormeasurement();
  if (Serial.available() > 0) {
    answer = Serial.read();
    switch (answer)
    {
      case 'I':
      turn_slightly_right();
      break;

      case 'E':
      turn_slightly_left();
      break;

      case 'F':
      move_forward();
      break;

      default:
      break;
    }
  }
}
