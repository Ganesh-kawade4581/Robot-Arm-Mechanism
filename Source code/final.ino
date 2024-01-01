#include <Servo.h>
#include <SoftwareSerial.h>

// Define the servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Define the motor control pins
int motorPin1 = 6;
int motorPin2 = 7;

// Define the joystick input pins
int joyPin1X = A0;
int joyPin1Y = A1;
int joyPin2X = A2;
int joyPin2Y = A3;

// Variables to store joystick values
int joy1X, joy1Y, joy2X, joy2Y;

// Map joystick values to servo/motor control range
int servoMin = 0;
int servoMax = 180;
int motorMin = -255;
int motorMax = 255;

// Define the Bluetooth module
SoftwareSerial bluetoothSerial(2, 3); // RX, TX

void setup() {
  // Attach the servo objects to the corresponding pins
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);

  // Set the motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Initialize the serial communication
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
}

void loop() {
  // Read joystick values
  joy1X = analogRead(joyPin1X);
  joy1Y = analogRead(joyPin1Y);
  joy2X = analogRead(joyPin2X);
  joy2Y = analogRead(joyPin2Y);

  // Map joystick values to servo/motor control range
  int servo1Angle = map(joy1X, 0, 1023, servoMin, servoMax);
  int servo2Angle = map(joy1Y, 0, 1023, servoMin, servoMax);
  int servo3Angle = map(joy2X, 0, 1023, servoMin, servoMax);
  int servo4Angle = map(joy2Y, 0, 1023, servoMin, servoMax);
  int motorSpeed = map(joy2Y, 0, 1023, motorMin, motorMax);

  // Control the servo motors
  servo1.write(servo1Angle);
  servo2.write(servo2Angle);
  servo3.write(servo3Angle);
  servo4.write(servo4Angle);

  // Control the DC motor
  if (motorSpeed > 0) {
    analogWrite(motorPin1, motorSpeed);
    analogWrite(motorPin2, 0);
  } else if (motorSpeed < 0) {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, -motorSpeed);
  } else {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
  }

  // Print the joystick and servo/motor values
  Serial.print("Joystick 1 X: ");
  Serial.print(joy1X);
  Serial.print("  Y: ");
  Serial.print(joy1Y);
  Serial.print("  Joystick 2 X: ");
}