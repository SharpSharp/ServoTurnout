#include "ServoTurnout.h"

void ServoTurnout::setup()
{
  targetPosition  = closedPosition;
  currentPosition = closedPosition;

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
}

void ServoTurnout::moveToThrown()
{
  targetPosition = thrownPosition;
}

void ServoTurnout::toggle()
{
  if (currentPosition == closedPosition) moveToThrown();
  if (currentPosition == thrownPosition) moveToClosed();
}

void ServoTurnout::targetPositionReached()
{ 
  servo.detach();
}

bool ServoTurnout::getThrownBit()
{
  if (currentPosition == thrownPosition) return true;
  else                                   return false;
}
bool ServoTurnout::getClosedBit()
{
  if (currentPosition == closedPosition) return true;
  else                                   return false;
}
bool ServoTurnout::getServoMoving()
{
  if ((currentPosition == closedPosition) || (currentPosition == thrownPosition))
    return false;
  else 
    return true;
}

void ServoTurnout::update()
{
  if (currentPosition != targetPosition) 
  {
    if (!servo.attached()) 
      servo.attach(servoPin);
      
    if (millis() > moveDelay)
    {
      moveDelay = millis() + TURNOUT_MOVE_SPEED;
      if (currentPosition < targetPosition) currentPosition++;
      if (currentPosition > targetPosition) currentPosition--;
      servo.write(currentPosition);
      
      if ((currentPosition == closedPosition) || (currentPosition == thrownPosition))
        targetPositionReached();
        
      if (frogPin > -1) 
      {
        if (currentPosition == ((closedPosition+thrownPosition)/2))
          digitalWrite(frogPin, !digitalRead(frogPin));
      }
    }
  }
}