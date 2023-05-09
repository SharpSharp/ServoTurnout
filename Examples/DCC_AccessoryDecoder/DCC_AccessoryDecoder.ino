#include <ServoTurnout.h>

//#define SERVO_PIN 9             // connect servo to pin 9
//#define TURNOUT_CLOSED 60       // angle of servo 60
//#define TURNOUT_THROWN 120      // angle of servo 120
//
//ServoTurnout turnout(SERVO_PIN, TURNOUT_CLOSED, TURNOUT_THROWN);

const byte NUMBER_OF_TURNOUTS = 3;

ServoTurnout turnouts[NUMBER_OF_TURNOUTS]= {
  {9,  60, 120},
  {10, 60, 120},
  {11, 60, 120}
};

#include <NmraDcc.h>
NmraDcc  Dcc;

// This function is called whenever a normal DCC Turnout Packet is received
// It returns the Acc Address (1 to 2044) 
// The Direction 0 (close) or 1 (throw)
// The Output Power true  (make sure it is active)
void notifyDccAccTurnoutOutput(uint16_t Addr, uint8_t Direction, uint8_t OutputPower)
{
 for (int i = 0; i < NUMBER_OF_TURNOUTS; i++)
 {
   if (Addr == i && OutputPower)
   {
      if (Direction)
      {
        turnouts[i].moveToClosed();
        break;
      }
      else
      {
        turnouts[i].moveToThrown();
        break;
      }
    }
  }
}
void setupDCCDecoder()
{
  // Setup which External Interrupt, the Pin it's associated with that we're using and enable the Pull-Up 
  Dcc.pin(0, 2, 1);

  // Call the main DCC Init function to enable the DCC Receiver
  Dcc.init(MAN_ID_DIY, 10, CV29_ACCESSORY_DECODER | CV29_OUTPUT_ADDRESS_MODE, 0);
}


void setup() {
  setupDCCDecoder();
  for (int i=0; i<NUMBER_OF_TURNOUTS; i++)
  {
    turnouts[i].setup();  
  }
}

void loop() {
  Dcc.process();
  for (int i=0; i<NUMBER_OF_TURNOUTS; i++)
  {   
    turnouts[i].update();
  }
}
