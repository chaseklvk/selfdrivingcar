/*
 * All controls for LEDs
 */

 #define LIGHT_RIGHT 10
 #define LIGHT_LEFT 4 

 void initLights() {
  pinMode(LIGHT_RIGHT, OUTPUT);
  pinMode(LIGHT_LEFT, OUTPUT);
 }

 void leftLightSteady() {
  digitalWrite(LIGHT_LEFT, HIGH);
 }

 void rightLightSteady() {
  digitalWrite(LIGHT_RIGHT, HIGH);
 }

 void leftLightOff() {
  digitalWrite(LIGHT_LEFT, LOW);
 }

 void rightLightOff() {
  digitalWrite(LIGHT_RIGHT, LOW);
 }

