#pragma once

#include <Arduino.h>
#include <Servo.h>

#define TURNOUT_MOVE_SPEED 20     // [ms] lower number is faster

class ServoTurnout
{
private:
  int servoPin;
  int closedPosition;
  int thrownPosition;
  int frogPin;
  Servo servo;
  int targetPosition;
  int currentPosition;
  unsigned long moveDelay;

public:
  ServoTurnout(int servoPin, int closedPosition, int thrownPosition, int frogPin = -1)
    : servoPin(servoPin), closedPosition(closedPosition), thrownPosition(thrownPosition), frogPin(frogPin)
    {
    }

  void setup();
  void update();
  void moveToClosed();
  void moveToThrown();
  void toggle();
  void targetPositionReached();
  
  bool getThrownBit();
  bool getClosedBit();
  bool getServoMoving();
};
