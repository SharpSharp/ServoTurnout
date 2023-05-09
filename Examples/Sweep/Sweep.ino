/* Turnout Sweep
 * 
 * An example to test the instalation of the Servo Turnout libary.
 * 
 * Mimics the Servo libaries Sweep Example
 * 
 * Servo moves through the full travel 0–180.
 * do NOT use on servo connected to a turnout
 *
 */
#include <ServoTurnout.h>

// attaches the servo on pin 9 
// goes from 0 degrees to 180 degrees
ServoTurnout turnout(9, 0, 180);

void setup() {
  turnout.setup();
  turnout.moveToThrown();
}

void loop() {
  if (turnout.getThrownBit()) 
    turnout.moveToClosed();
  
  if (turnout.getClosedBit()) 
    turnout.moveToThrown();
 
  turnout.update();
}
