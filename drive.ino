/* 
 * All controls for DC motors
 */

// Define Pins
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

// Initialize motors
void initMotors() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

// Move car forward
void moveForward(int i) {
  setSpeed(i);
  digitalWrite(IN1, HIGH);            // Set IN1 high
  digitalWrite(IN2, LOW);             // Set IN2 low
  digitalWrite(IN3, LOW);             // Set IN3 low
  digitalWrite(IN4, HIGH);            // Set IN4 high

  // Lights
  leftLightOff();
  rightLightOff();
}

void moveBack(int i) {
  setSpeed(i);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  leftLightOff();
  rightLightOff();
}

void moveLeft(int i) {
  setSpeed(i);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  leftLightSteady();
}

void moveRight(int i) {
  setSpeed(i);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  rightLightSteady();
}

void stopMotors() {
  digitalWrite(ENB, LOW);
  digitalWrite(ENA, LOW);

  leftLightOff();
  rightLightOff();
}

void setSpeed(int i) {
  analogWrite(ENB, i);
  analogWrite(ENA, i);
}

