/******************************************
 * Robot Car Project - Engineering 44
 * Chase Zimmerman
 * 4/10/18
 *****************************************/
 
// Initial Conditions
// What's the initial distance from the wall?
int INITIAL_DISTANCE = 0;
int INITIAL_DISTANCE_FRONT = 0;
int SIDE = -1;             // 1 = Left Side, 0 = Right Side


// Parking Parameters
int THRESHOLD = 15;
int FINAL_THRESHOLD = 20;
int PARK_TURN_SPEED = 250;
int PARK_TIME_DELAY = 500;
int FRONT_DETECTION_DISTANCE = 10;
int FORWARD_SPEED_AFTER_TURN = 75;
int FORWARD_CORRECTION_DELAY = 100;

// Is first turn complete?
bool firstTurn = false;

// Is second turn complete?
bool secondTurn = false;

// Is the car parking?
bool isParking = false;

// Is the car parked?
bool parked = false;

// Parallel park?
bool parallel = false;

void setup() {
  Serial.begin(9600);
  
  // initialize the motors
  initMotors();
  initSensors();
  initSpeaker();
  initLights();
  initServo();

  initCar();

  delay(1000); // Nop
}

/* Notes:
 * 255 = fast, 100 = slow
*/

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(measureDistanceFront(true));

  // Check if we're parked, if so return from func
  if (parked) {
    stopMotors();
    
    leftLightSteady();
    rightLightSteady();
    delay(100);
    leftLightOff();
    rightLightOff();
  }
 
  /*
   * Car is searching for a spot
   * 
   */
  if (!isParking) {
    // Code for normal operation


    // Correct distance
    //if (millis() - lastRefresh >= REFRESH_TIME) {
      //lastRefresh = millis();
      //correctDistance();
    //}
      
      detectFrontObstacle();
      searchForSpot();
          
  } else if (parallel && isParking) { 
    parallelPark();  
  } else {
    // Car has found a spot, running the parking code
    if (SIDE == 0) {
      // Right
      parkRightSide();
    } else if (SIDE == 1) {
      // Left
      parkLeftSide();
    }
  }
  
}


