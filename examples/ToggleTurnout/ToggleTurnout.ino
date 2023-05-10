/*
 * An example of driving a turnout using a single push button
 *
 * The ServoTurnout library is designed to enable a servo to
 * slowly move a model railway turnout from it's closed position
 * to it's thrown posistion. Importantly it does this without 
 * using delay which means that the Arduino remains resonsive
 * to inputs such as push buttons. 
 * In this exampole a single turnout can be controlled by a servo
 * connected to pin 9, by a push button contected to pin 4. The
 * turnout will move between the closed and the thrown positions
 * on the first press of the button. On second press it will 
 * return from thrown to closed. It will to continue to toggle 
 * to the other position on each button press. 
 * Change the TURNOUT_CLOSED and TURNOUT_THROWN to adjust the 
 * range of movement of the servo
 */

#include <ServoTurnout.h>

#define PUSH_BUTTON_PIN 4       // connect push buttun to pin 4
#define SERVO_PIN 9             // connect servo to pin 9
#define TURNOUT_CLOSED 60       // angle of servo 60
#define TURNOUT_THROWN 120      // angle of servo 120

ServoTurnout turnout(SERVO_PIN, TURNOUT_CLOSED, TURNOUT_THROWN);
 
 void setup() {
  turnout.setup();
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(PUSH_BUTTON_PIN) == LOW)
    turnout.toggle();
  
  // turnout.update() must be called from the loop to move the servo to it's tagert position
  turnout.update();
}
