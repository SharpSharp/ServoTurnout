/*
 * 
 */

#include <ServoTurnout.h>

#define ROUTE_1_PIN 4
#define ROUTE_2_PIN 5

const byte NUMBER_OF_TURNOUTS = 3;


ServoTurnout turnouts[NUMBER_OF_TURNOUTS]= {
  {9,  60, 120},
  {10, 60, 120},
  {11, 60, 120}
};
 
 void setup() {
  for (int i=0; i<NUMBER_OF_TURNOUTS; i++)
  {
    turnouts[i].setup();  
  }

  pinMode(ROUTE_1_PIN, INPUT_PULLUP);
  pinMode(ROUTE_2_PIN, INPUT_PULLUP);
}

void loop() {
  // 1: read buttons and set routes
  if (digitalRead(ROUTE_1_PIN) == LOW)
  {
    turnouts[0].moveToClosed();
    turnouts[1].moveToClosed();
    turnouts[2].moveToClosed();
  }
    if (digitalRead(ROUTE_2_PIN) == LOW)
  {
    turnouts[0].moveToThrown();
    turnouts[1].moveToThrown();
    turnouts[2].moveToThrown();
  }
  
  // 2: move turnouts

  for (int i=0; i<NUMBER_OF_TURNOUTS; i++)
  {   
    turnouts[i].update();
    if (turnouts[i].getServoMoving())  // ensure only one turnout moves at a time
      break;                           // removal of this if statement allows multiple turnouts to movement at once
  }
}
