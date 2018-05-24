/*
 * Initialization and controls for LEDs
 */

// Define the pins we'll use
 #define LIGHT_RIGHT 10
 #define LIGHT_LEFT 4 

/* initLights()
 * 
 * Initialize the pins for output.
 * 
 */
 void initLights() {
  pinMode(LIGHT_RIGHT, OUTPUT);
  pinMode(LIGHT_LEFT, OUTPUT);
 }

/* leftLightSteady()
 * 
 * Turn on the left light.
 * 
 */
 void leftLightSteady() {
  digitalWrite(LIGHT_LEFT, HIGH);
 }

/* rightlightSteady()
 * 
 * Turn on the right light.
 * 
 */
 void rightLightSteady() {
  digitalWrite(LIGHT_RIGHT, HIGH);
 }

/* leftLightOff()
 * 
 * Turn off the left light.
 * 
 */
 void leftLightOff() {
  digitalWrite(LIGHT_LEFT, LOW);
 }

/* rightLightOff()
 * 
 * Turn off the right light.
 * 
 */
 void rightLightOff() {
  digitalWrite(LIGHT_RIGHT, LOW);
 }

