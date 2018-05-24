/*
 * Initialization and controls for servo motor.
 * 
 */

// Include servo library
#include <Servo.h>

// Create servo instance
Servo myservo;

/* initServo()
 * 
 * Attach servo to pin
 * 
 */
void initServo() {
  myservo.attach(3);    
}

/* setServoFront()
 * 
 * Point servo straight ahead
 * 
 */
void setServoFront() {
  myservo.write(90);
}


/* setServoLeft()
 * 
 * Point servo to the left side.
 * 
 */
void setServoLeft() {
  myservo.write(173);
}

/* setServoRight()
 * 
 * Point servo to the right side.
 * 
 */
void setServoRight() {
  myservo.write(17);
}

