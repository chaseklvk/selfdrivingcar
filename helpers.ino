/*
 * 
 * HELPER METHODS
 * 
 */

/*
 * Initialize car
 */ 
void initCar() {
  delay(1000);    //nop
  //Measure Wall Distances
  int distanceLeft = measureDistanceLeft();           // Get measurement from left sensor
  int distanceRight = measureDistanceRight();         // Get measurement from right sensor  

  // Which distance is greater? 
  if (distanceLeft < distanceRight) {
    // Left distance is less
    INITIAL_DISTANCE = distanceLeft;
    SIDE = 1;
  } else {
    // Right distance is less
    INITIAL_DISTANCE = distanceRight;
    SIDE = 0;
  }

  if (SIDE == 1) {
    // Left

    setServoLeft();

    INITIAL_DISTANCE_FRONT = measureDistanceFront(true);
    
  } else if (SIDE == 0) {
    // Right 

    setServoRight();
    
    INITIAL_DISTANCE_FRONT = measureDistanceFront(true);
  }
  /*
   // negative => correct left
   // positive => correct right
   // until difference is -5
   int difference = INITIAL_DISTANCE - INITIAL_DISTANCE_FRONT;

   if (difference < 0) {
    //correct left until -5

    while(difference < -4) {

      if (SIDE == 1) {
        moveLeft(250);
        INITIAL_DISTANCE = measureDistanceLeft();
        INITIAL_DISTANCE_FRONT = measureDistanceFront();
      } else if(SIDE == 0) {
        moveRight(250);
        INITIAL_DISTANCE = measureDistanceRight();
        INITIAL_DISTANCE_FRONT = measureDistanceFront();
      }

      difference = INITIAL_DISTANCE - INITIAL_DISTANCE_FRONT;
    }
    
    stopMotors();
    
   } else {
    // correct right until -5

    while(difference > -4) {

      if (SIDE == 1) {
        moveRight(250);
        INITIAL_DISTANCE = measureDistanceLeft();
        INITIAL_DISTANCE_FRONT = measureDistanceFront();
      } else if(SIDE == 0) {
        moveLeft(250);
        INITIAL_DISTANCE = measureDistanceRight();
        INITIAL_DISTANCE_FRONT = measureDistanceFront();
        
      }

      difference = INITIAL_DISTANCE - INITIAL_DISTANCE_FRONT;
    }

    stopMotors();
   } */
}

/*
 * Detects wall distance and makes the appropriate correction
 * 
 */
/*void correctDistance() {

   int difference = INITIAL_DISTANCE - INITIAL_DISTANCE_FRONT;

   if (SIDE == 1) 
    setServoLeft();
   else
    setServoRight();

   if (difference < 0) {
    //correct left until -5

    while(difference < -4) {

      if (SIDE == 1) {
        moveLeft(250);
        INITIAL_DISTANCE = measureDistanceLeft();
        INITIAL_DISTANCE_FRONT = measureDistanceFront(false);
      } else if(SIDE == 0) {
        moveRight(250);
        INITIAL_DISTANCE = measureDistanceLeft();
        INITIAL_DISTANCE_FRONT = measureDistanceFront(false);
      }
    }
  
   } else {
    // correct right until -5

    while(difference > -4) {

      if (SIDE == 1) {
        moveRight(250);
        INITIAL_DISTANCE = measureDistanceLeft();
        INITIAL_DISTANCE_FRONT = measureDistanceFront(false);
      } else if(SIDE == 0) {
        moveLeft(250);
        INITIAL_DISTANCE = measureDistanceLeft();
        INITIAL_DISTANCE_FRONT = measureDistanceFront(false);
      }
    }
    
   }
   
   moveForward(100);
} */

/*
 * Detects a front obstacle and stops if it's in the way
 * 
 */
void detectFrontObstacle() {
  // Set the servo to the front
  setServoFront();

  // Make measurement
  int distance = measureDistanceFront(false);

  if (distance > 15) {
    moveForward(100);
  } else {
    stopMotors();  
  }
}

/*
 * Search for spot
 * 
 */

void searchForSpot() {
  if (SIDE == 1) {
    // Left
    int distanceLeft = measureDistanceLeft();

    if (distanceLeft >= INITIAL_DISTANCE + THRESHOLD) verifySpotIsOpen();

  } else if (SIDE == 0) {
    // Right
    int distanceRight = measureDistanceRight();

    if (distanceRight >= INITIAL_DISTANCE + THRESHOLD) verifySpotIsOpen();
  }
}

void verifySpotIsOpen() {
  if (SIDE == 1) {
    // Left

    // Stop the car
    stopMotors();
    
    // Set servo to the left
    setServoLeft();

    // Measure left-front distance 
    int distanceLeft = measureDistanceFront(true);

    // If the space is clear, park
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

    // If the space is clear, park
    if (distanceRight >= INITIAL_DISTANCE_FRONT + THRESHOLD) {
      isParking = true;
    } else {
      moveForward(100);
      delay(500);
    }
  }
}

void parkLeftSide() {

  // Turn 90 degrees
  if (!firstTurn) {
    firstTurn = true;
    moveForward(100);
    delay(FORWARD_CORRECTION_DELAY);
    moveLeft(PARK_TURN_SPEED);
    delay(PARK_TIME_DELAY);
    stopMotors();
  }

  // Set servo front
  setServoFront();

  // Move forward until back wall
  delay(500);
  int distanceFront = measureDistanceFront(false);

  if (distanceFront > FRONT_DETECTION_DISTANCE) {
    moveForward(FORWARD_SPEED_AFTER_TURN);
  } else {
    stopMotors();

    finalCheckLeft();
  }
}

void parkRightSide() {

  // Turn 90 degrees
  if (!firstTurn) {
    firstTurn = true;
    moveForward(100);
    delay(FORWARD_CORRECTION_DELAY);
    moveRight(PARK_TURN_SPEED);
    delay(PARK_TIME_DELAY);
    stopMotors();
  }

  // Set servo front
  setServoFront();

  // Move forward until back wall
  delay(500);
  int distanceFront = measureDistanceFront(false);

  if (distanceFront > FRONT_DETECTION_DISTANCE) {
    moveForward(FORWARD_SPEED_AFTER_TURN);
  } else {
    stopMotors();

    finalCheckRight();
  }
}

void finalCheckRight() {
  setServoLeft();
  int leftDistance = measureDistanceFront(true);

  //setServoRight();
  //int rightDistance = measureDistanceFront(true);

  if (leftDistance > FINAL_THRESHOLD) {
    moveLeft(PARK_TURN_SPEED);
    delay(PARK_TIME_DELAY);
    stopMotors();

    int distanceFront = measureDistanceFront(true);

    if (distanceFront > 400) {
      // back to drive mode

      firstTurn = false;
      isParking = false;
      parked = false;
      secondTurn = false;

      // TODO
    } else {
      // move until we hit an obstacle
      parallel = true; 
    }
  } else {
    parked = true;
  }
}

void finalCheckLeft() {
  setServoRight();
  int rightDistance = measureDistanceFront(true);

  //setServoRight();
  //int rightDistance = measureDistanceFront(true);

  if (rightDistance > FINAL_THRESHOLD) {
    moveRight(PARK_TURN_SPEED);
    delay(PARK_TIME_DELAY);
    stopMotors();

    int distanceFront = measureDistanceFront(true);

    if (distanceFront > 400) {
      // back to drive mode

      firstTurn = false;
      isParking = false;
      parked = false;
      secondTurn = false;

      // TODO
    } else {
      // move until we hit an obstacle
      parallel = true; 
    }
  } else {
    parked = true;
  }
}

void parallelPark() {
  // Set the servo to the front
  setServoFront();

  // Make measurement
  int distance = measureDistanceFront(false);

  if (distance > FRONT_DETECTION_DISTANCE) {
    moveForward(FORWARD_SPEED_AFTER_TURN);
  } else {
    stopMotors();  
    parked = true;
  }
}

