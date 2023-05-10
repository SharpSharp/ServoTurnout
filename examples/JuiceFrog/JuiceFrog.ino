/*
 * 
 */

#include <ServoTurnout.h>

#define PUSH_BUTTON_PIN 4       // connect push buttun to pin 4
#define SERVO_PIN 9             // connect servo to pin 9
#define FROG_PIN 12             // connect relay to pin 12
#define TURNOUT_CLOSED 60       // angle of servo 60
#define TURNOUT_THROWN 120      // angle of servo 120

ServoTurnout turnout(SERVO_PIN, TURNOUT_CLOSED, TURNOUT_THROWN, FROG_PIN);
 
 void setup() {
  turnout.setup();
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(PUSH_BUTTON_PIN) == LOW)
  {
    turnout.toggle();
  }
  turnout.update();
}
