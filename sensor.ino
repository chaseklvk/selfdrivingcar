/*
 * Initialization and controls for ultrasonic sensors
 */

// Define the pins we'll use
 #define ECHO_LEFT A1
 #define TRIG_LEFT A0
 #define ECHO_RIGHT A3
 #define TRIG_RIGHT A2
 #define TRIG_FRONT A5
 #define ECHO_FRONT A4

/* initSensors()
 * 
 * Set the appropriate pins for ouput
 * 
 */
 void initSensors() {
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
}


/* measureDistanceLeft()
 * 
 * Measure the distance of the left side sensor
 * 
 */
int measureDistanceLeft() {
  
  digitalWrite(TRIG_LEFT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_LEFT, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_LEFT, LOW);

  float Fdistance = pulseIn(ECHO_LEFT, HIGH);
  Fdistance = Fdistance / 58;

  return (int)Fdistance;
}

/* measureDistanceRight()
 * 
 * Measure the distance of the right side sensor
 * 
 */
int measureDistanceRight() {
  
  digitalWrite(TRIG_RIGHT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_RIGHT, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_RIGHT, LOW);

  float Fdistance = pulseIn(ECHO_RIGHT, HIGH);
  Fdistance = Fdistance / 58;

  return (int)Fdistance;
}

/* measureDistanceFront()
 * 
 * Measure the distance of the front sensor
 * 
 */
int measureDistanceFront(bool scanDelay) {
  if (scanDelay) delay(2000);
  
  digitalWrite(TRIG_FRONT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_FRONT, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_FRONT, LOW);

  float Fdistance = pulseIn(ECHO_FRONT, HIGH);
  Fdistance = Fdistance / 58;

  return (int)Fdistance;
}

