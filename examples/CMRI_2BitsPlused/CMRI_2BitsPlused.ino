/*
 * 
 */

#include <CMRI.h>

CMRI cmri; // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs

#include <ServoTurnout.h>

#define SERVO_PIN 9             // connect servo to pin 9
#define TURNOUT_CLOSED 60       // angle of servo 60
#define TURNOUT_THROWN 120      // angle of servo 120

ServoTurnout turnout(SERVO_PIN, TURNOUT_CLOSED, TURNOUT_THROWN);
 
 void setup() {
  Serial.begin(9600, SERIAL_8N2); // make sure this matches your speed set in JMRI
  turnout.setup();
}

void loop() {
  // 1: build up a packet
  cmri.process();
  
  // 2: update output from CMRI
  // check to see if CMRI is sending a turnout bits
  if (cmri.get_bit(0)) turnout.moveToClosed();
  if (cmri.get_bit(1)) turnout.moveToThrown();
  }

  // 3: update input to CMRI
  // send thrown and closed bits for 2 sensor Turnout feedback
  cmri.set_bit(0, turnout.getThrownBit());
  cmri.set_bit(1, turnout.getClosedBit());

  // 4: move turnout 
  turnout.update();
}
