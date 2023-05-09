#include "ServoTurnout.h"

void ServoTurnout::setup()
{
  targetPosition  = closedPosition;
  currentPosition = closedPosition;
  isClosed = true;
  isThrown = false;
  isServoMoving = false;

  servo.attach(servoPin);
  servo.write(currentPosition);

  if (frogPin > -1) 
  {
    pinMode(frogPin, OUTPUT);
    digitalWrite(frogPin, HIGH);
  }

  delay(200);
  servo.detach();
  moveToClosed();
}

void ServoTurnout::moveToClosed()
{
  targetPosition = closedPosition;
  isThrown = false;   // now change sensor as turnout is no longer thrown
}

void ServoTurnout::moveToThrown()
{
  targetPosition = thrownPosition;
  isClosed = false;   // now change sensor as turnout is no longer closed
}

void ServoTurnout::toggle()
{
  if (isClosed) moveToThrown();
  if (isThrown) moveToClosed();
}

void ServoTurnout::targetPositionReached()
{ 
  servo.detach();
  isServoMoving = false;
}

bool ServoTurnout::getThrownBit()
{
  return isThrown;
}
bool ServoTurnout::getClosedBit()
{
  return isClosed;
}
bool ServoTurnout::getServoMoving()
{
  return isServoMoving;
}

void ServoTurnout::update()
{
  if (currentPosition != targetPosition) 
  {
    if (!isServoMoving) 
    {
      servo.attach(servoPin);
      isServoMoving = true;
    }
    if(millis() > moveDelay)
    {
      moveDelay = millis() + TURNOUT_MOVE_SPEED;
      if (currentPosition < targetPosition) currentPosition++;
      if (currentPosition > targetPosition) currentPosition--;
      servo.write(currentPosition);
      
      if (currentPosition == closedPosition)
      {
        isClosed = true;
        if (frogPin > -1) digitalWrite(frogPin, HIGH);
        targetPositionReached();
      }
      if (currentPosition == thrownPosition)
      {
        isThrown = true;
        if (frogPin > -1) digitalWrite(frogPin, LOW);
        targetPositionReached();
      }  
    }
  }
}
