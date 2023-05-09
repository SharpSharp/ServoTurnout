=	ServoTurnout
An Arduino library to control a Turnout servo on a model railway. This library can be used to slowly throw a turnout. It is  non-blocking, it does not use delay, this ensures that an Arduino remains resposive while the servo moves.

Using the ServoTurnout library

To use the library include the ServoTurnout.h header file.

Create an instance of the library with the pin number, thrown and closed positions.

ServoTurnout turnout(servoPin, closedPosition, thrownPosition);


