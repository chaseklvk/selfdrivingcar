/*
 * All controls for sounds WIP
 */

#define SPEAKER 2

 void initSpeaker() {
  pinMode(SPEAKER, OUTPUT);
 }

 void beep() {
  digitalWrite(SPEAKER, HIGH);
 }

