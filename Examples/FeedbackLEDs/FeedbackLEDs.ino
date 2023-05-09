/*
 * 
 */

#include <ServoTurnout.h>

#define PUSH_BUTTON_PIN 4       // connect push buttun to pin 4
#define CLOSED_LED_PIN 5        // connect LED to pin 5
#define THROWN_LED_PIN 6        // connect LED to pin 6
#define SERVO_PIN 9             // connect servo to pin 9
#define TURNOUT_CLOSED 60       // angle of servo 60
#define TURNOUT_THROWN 120      // angle of servo 120

ServoTurnout turnout(SERVO_PIN, TURNOUT_CLOSED, TURNOUT_THROWN);
 
 void setup() {
  turnout.setup();
  
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);
  pinMode(CLOSED_LED_PIN, OUTPUT);
  pinMode(THROWN_LED_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(PUSH_BUTTON_PIN) == LOW)
  {
    turnout.toggle();
  }
  
  digitalWrite(CLOSED_LED_PIN, turnout.getClosedBit());
  digitalWrite(THROWN_LED_PIN, turnout.getThrownBit());
  
  turnout.update();
}
