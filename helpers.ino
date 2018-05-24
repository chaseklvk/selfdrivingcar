/*
 * 
 * HELPER METHODS
 * 
 */

/* initCar()
 * 
 * Initializes the car. Takes initial distance readings and sets initial conditions.
 * 
 */ 
void initCar() {
  delay(1000);    //nop
  
  //Measure Wall Distances
  int distanceLeft = measureDistanceLeft();           // Get measurement from left sensor
  int distanceRight = measureDistanceRight();         // Get measurement from right sensor  

  // Which distance is greater? 
  if (distanceLeft < distanceRight) {
    // Left distance is less
    
    INITIAL_DISTANCE = distanceLeft;                  // Set initial side distance to the left measurement
    SIDE = 1;                                         // Set our side integer to 1 to indicate left
    
  } else {
    // Right distance is less
    
    INITIAL_DISTANCE = distanceRight;                 // Set initial side distance to the right measurement
    SIDE = 0;                                         // Set our side integer to 0 to indicate right
    
  }

  // Now we want a measurement from the front sensor. First check what side we're on
  if (SIDE == 1) {
    // Left

    setServoLeft();                                                   // Set servo to left side

    INITIAL_DISTANCE_FRONT = measureDistanceFront(true);              // Measure the distance on the front sensor
    
  } else if (SIDE == 0) {
    // Right 

    setServoRight();                                                  // Set servo to right side
    
    INITIAL_DISTANCE_FRONT = measureDistanceFront(true);              // Measure the distance on the front sensor
  }
}

/* detectFrontObstacle()
 * 
 * Detects a front obstacle and stops if it's in the way.
 * 
 */
void detectFrontObstacle() {
  // Set the servo to the front
  setServoFront();

  // Make measurement
  int distance = measureDistanceFront(false);


  // Stop the car if less than a certain threshold
  if (distance > 15) {
    
    moveForward(100);
    
  } else {
    
    stopMotors();  
    
  }
}

/* searchForSpot()
 *  
 * Search for a parking spot and run verify method if found.
 * 
 */
void searchForSpot() {
  if (SIDE == 1) {
    // Left
    
    int distanceLeft = measureDistanceLeft();                                       // Take a distance measurement

    if (distanceLeft >= INITIAL_DISTANCE + THRESHOLD) verifySpotIsOpen();           // Greater than threshold? Verify that the spot is open

  } else if (SIDE == 0) {
    // Right
    
    int distanceRight = measureDistanceRight();                                     // Take a distance measurement

    if (distanceRight >= INITIAL_DISTANCE + THRESHOLD) verifySpotIsOpen();          // Greater than threshold? Verify that the spot is open
  }
}

/* verifySpotIsOpen()
 * 
 * Use the front sensor to check that we've found a valid spot.
 * 
 */
void verifySpotIsOpen() {
  if (SIDE == 1) {
    // Left

    // Stop the car
    stopMotors();
    
    // Set servo to the left
    setServoLeft();

    // Measure left-front distance 
    int distanceLeft = measureDistanceFront(true);

    // If the space is clear, park. Else: move forward slightly and try again.
    if (distanceLeft >= INITIAL_DISTANCE_FRONT + THRESHOLD) { 
      
      isParking = true;
      
    } else {
      
      moveForward(100);
      delay(500);
      
    }
    
  } else if (SIDE == 0) {
    // Right

    //delay(50);
    // Stop the car
    stopMotors();

    // Set servo to the left
    setServoRight();

    // Measure left-front distance 
    int distanceRight = measureDistanceFront(true);

    // If the space is clear, park. Else: move forward slightly and try again.
    if (distanceRight >= INITIAL_DISTANCE_FRONT + THRESHOLD) {
      
      isParking = true;
      
    } else {
      
      moveForward(100);
      delay(500);
      
    }
  }
}

/* parkLeftSide()
 * 
 * Park the car w/ spot on left side
 * 
 */
void parkLeftSide() {

  // Turn 90 degrees into the spot but only once! Hence the boolean.
  if (!firstTurn) {
    
    firstTurn = true;                              

    // Move the car into perpendicular position
    moveForward(100);
    delay(FORWARD_CORRECTION_DELAY);
    moveLeft(PARK_TURN_SPEED);
    delay(PARK_TIME_DELAY_LEFT);

    // Stop
    stopMotors();
    
  }

  // Set servo front
  setServoFront();

  // Move forward until we detect the back wall of the parking spot
  delay(500);
  int distanceFront = measureDistanceFront(false);

  if (distanceFront > FRONT_DETECTION_DISTANCE) {
    
    moveForward(FORWARD_SPEED_AFTER_TURN);
    
  } else {
    stopMotors();

    finalCheckLeft();                                   // We've found the wall, check if we can parallel park
  }
}

void parkRightSide() {

  // Turn 90 degrees into the spot but only once! Hence the boolean.
  if (!firstTurn) {
    
    firstTurn = true;

    // Move the car into perpendicular position
    moveForward(100);
    delay(FORWARD_CORRECTION_DELAY);
    moveRight(PARK_TURN_SPEED);
    delay(PARK_TIME_DELAY_RIGHT);

    // Stop
    stopMotors();
  }

  // Set servo front
  setServoFront();

  // Move forward until we detect the back wall of the parking spot
  delay(500);
  int distanceFront = measureDistanceFront(false);

  if (distanceFront > FRONT_DETECTION_DISTANCE) {
    
    moveForward(FORWARD_SPEED_AFTER_TURN);
  
  } else {
    stopMotors();

    finalCheckRight();                              // We've found the wall, check if we can parallel park
  }
}

/* finalCheckRight()
 * 
 * We've successfully perpendicular parked. Now check if the
 * spot is large enough to parallel park.
 * 
 */
void finalCheckRight() {

  // Set servo the the left side and measure the distance
  setServoLeft();
  int leftDistance = measureDistanceFront(true);

  // Is the distance great enough? Yes: turn car 90 degrees. No: we're parked
  if (leftDistance > FINAL_THRESHOLD) {

    // Move 90 degrees to the left
    moveLeft(PARK_TURN_SPEED);
    delay(PARK_TIME_DELAY_LEFT);
    stopMotors();

    // Measure the distance
    int distanceFront = measureDistanceFront(true);

    // Greater than 50? We probably aren't in a spot... change back to drive mode
    if (distanceFront > 50) {
      // back to drive mode

      firstTurn = false;
      isParking = false;
      parked = false;
      secondTurn = false;

    } else {
      // We are in a spot, set the parallel flag.
      
      parallel = true; 
    }
  } else {
    // This is a perpendicular spot. Set parked flag.
    
    parked = true;
  }
}

/* finalCheckLeft()
 * 
 * We've successfully perpendicular parked. Now check if the
 * spot is large enough to parallel park.
 * 
 */
void finalCheckLeft() {

  // Set servo the the left side and measure the distance
  setServoRight();
  int rightDistance = measureDistanceFront(true);

  // Is the distance great enough? Yes: turn car 90 degrees. No: we're parked
  if (rightDistance > FINAL_THRESHOLD) {

    // Move the car 90 degrees to the right
    moveRight(PARK_TURN_SPEED);
    delay(PARK_TIME_DELAY_RIGHT);
    stopMotors();

    // Measure the distance
    int distanceFront = measureDistanceFront(true);

    // Greater than 50? We probably aren't in a spot... change back to drive mode
    if (distanceFront > 50) {
      // back to drive mode

      firstTurn = false;
      isParking = false;
      parked = false;
      secondTurn = false;

    } else {
      // We are in a spot, set the parallel flag
      
      parallel = true; 
    }
  } else {
    // This is a perpendicular spot. Set parked flag.
    
    parked = true;
  }
}

/* parallelPark()
 * 
 * We've determined the space is large enough, parallel park the car.
 * 
 */
void parallelPark() {
  // Set the servo to the front
  setServoFront();

  // Make measurement
  int distance = measureDistanceFront(false);

  // Move forward until we detect the side wall and stop the car.
  if (distance > FRONT_DETECTION_DISTANCE) {
    
    moveForward(FORWARD_SPEED_AFTER_TURN);
    
  } else {
    
    stopMotors();  
    parked = true;
    
  }
}

