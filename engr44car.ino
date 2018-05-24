/******************************************
 * Robot Car Project - Engineering 44
 * Chase Zimmerman, Jason, Jared, Gino
 * 4/10/18
 *****************************************/
 
/*
 * INITIAL CONDITIONS
 */
int INITIAL_DISTANCE = 0;                       // Initial distance measured by the side sensor
int INITIAL_DISTANCE_FRONT = 0;                 // Initial distance measured by the front sensor 
int SIDE = -1;                                  // 1 = Left Side, 0 = Right Side


// Parking Parameters
int THRESHOLD = 15;                             // Threshold for perpendicular parking space (distance beyond initial distance)
int FINAL_THRESHOLD = 20;                       // Threshold for parallel parking space (measured once in spot parallel)
int PARK_TURN_SPEED = 250;                      // Turning speed of the car in parking mode
int PARK_TIME_DELAY_LEFT = 300;                 // Turning time delay for left turn
int PARK_TIME_DELAY_RIGHT = 330;                // Turning time delay for right turn
int FRONT_DETECTION_DISTANCE = 10;              // Distance to stop when front obstace detected in parking mode
int FORWARD_SPEED_AFTER_TURN = 75;              // Speed to travel after turning to parallel park
int FORWARD_CORRECTION_DELAY = 100;             // Delay used to move the car forward slightly after detecting a space

// Is first turn complete (perpendicular parking)?
bool firstTurn = false;                         

// Is second turn complete (parallel parking)?
bool secondTurn = false;

// Is the car parking?
bool isParking = false;

// Is the car parked?
bool parked = false;

// Parallel park?
bool parallel = false;

// Used to run code in the loop every REFRESH_TIME milliseconds
int lastRefresh = 0;                          
int REFRESH_TIME = 3000;

/* Setup()
 *  
 * Each file has its own init method. Each method is run to initialize the component.
 * Finally, initCar is run to measure our initial distances.
 * 
 */

void setup() {
  Serial.begin(9600);
  
  initMotors();
  initSensors();
  initLights();
  initServo();

  initCar();

  delay(1000); // Nop
}

/* Loop()
 * 
 * Main program loop, checks the status of the car using the booleans defined above.
 * 
 */

void loop() {

  // Are we parked? Yes: flash lights and stop moving, No: continue
  if (parked) {
    stopMotors();
    setServoFront();
    
    // Correct distance
    if (millis() - lastRefresh >= REFRESH_TIME) {
      lastRefresh = millis();
      leftLightOff();
      rightLightOff();
      while(1);
    }
    
    leftLightSteady();
    rightLightSteady();
    delay(50);
    leftLightOff();
    rightLightOff();
  }

  // Are we in the process of parking?
  if (!isParking) {
    // Driving mode
      
      detectFrontObstacle();                        // Detect obstacles in the front while moving
      searchForSpot();                              // Use the back sensors to search for a spot
          
  } else if (parallel && isParking) { 
    
    parallelPark();                                 // Parallel park the car is parallel and isParking are true
    
  } else {
    // Car has found a potential spot, run a different method depending on the side of the wall
    
    if (SIDE == 0) {
      // Right
      
      parkRightSide();                              // Start parking procedure for right hand wall
      
    } else if (SIDE == 1) {
      // Left
      
      parkLeftSide();                               // Start parking procedure for left hand wall
      
    }
  }
}


