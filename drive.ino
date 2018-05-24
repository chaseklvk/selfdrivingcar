/* 
 * Initialization and controls for DC Motors
 */

// Define Pins
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

/* initMotors()
 * 
 * Set the pinMode for the appropriate pins defined above.
 * 
 */
void initMotors() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

/* moveForward(int i)
 * 
 * Move the car forward. Takes an integer value to set the speed.
 * 
 */
void moveForward(int i) {
  setSpeed(i);
  digitalWrite(IN1, HIGH);            // Set IN1 high
  digitalWrite(IN2, LOW);             // Set IN2 low
  digitalWrite(IN3, LOW);             // Set IN3 low
  digitalWrite(IN4, HIGH);            // Set IN4 high

  // Moving forward, no turn signal required
  leftLightOff();
  rightLightOff();
}

/* moveBack(int i)
 * 
 * Move the car backward. Takes an integer value to set the speed.
 * 
 */
void moveBack(int i) {
  setSpeed(i);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);


  // Moving backward, no turn signal required
  leftLightOff();
  rightLightOff();
}

/* moveLeft(int i)
 * 
 * Move the car to the left. Takes an integer value to set the speed.
 * 
 */
void moveLeft(int i) {
  setSpeed(i);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // Left turn signal
  leftLightSteady();
}

/* moveRight(int i)
 * 
 * Move the car to the right. Takes an integer value to set the speed.
 * 
 */
void moveRight(int i) {
  setSpeed(i);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);


  // Right turn signal
  rightLightSteady();
}

/* stopMotors()
 * 
 * Stop the car.
 * 
 */
void stopMotors() {
  digitalWrite(ENB, LOW);
  digitalWrite(ENA, LOW);

  leftLightOff();
  rightLightOff();
}

/* setSpeed(int i)
 * 
 * Set the speed of the motors. Takes an integer value for the speed. 
 * Used here as more of a private method not meant to be accessed directly. 
 */
void setSpeed(int i) {
  analogWrite(ENB, i);
  analogWrite(ENA, i);
}

