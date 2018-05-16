/*
 * All controls for servo
 * 3.5
 * Right about 17
 * Left about 173
 * Forward about 90
 */

 

#include <Servo.h>
Servo myservo;

void initServo() {
  myservo.attach(3);     // Attack servo to pin 3
}

void setServoFront() {
  myservo.write(90);
}

void setServoLeft() {
  myservo.write(173);
}

void setServoRight() {
  myservo.write(17);
}

