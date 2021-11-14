/**
 * Hand Scanner 5000
 *
 * Simulated hand scanner 
 * for E's 3rd Grade Class
 */
#include <Arduino.h>
#include "bsp.h"

//=========================================================
//- Heartbeat Function
//-  strobe the onboard LED to indicate active loop
//=========================================================
void heartbeat(void) 
{
    blinkLED(ONBOARD_LED, 2);
}

//=========================================================
//- Setup
//-  init routine for arduino
//=========================================================
void setup() 
{
  //setup serial monitor
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  //configure heartbeat LED
  configureLED(ONBOARD_LED);
}

//=========================================================
//- Loop
//-  main control loop for arduino
//=========================================================
void loop() 
{
  // run heartbeat
  heartbeat();
  
  delay(1000);
  Serial.println("Test Console");
}