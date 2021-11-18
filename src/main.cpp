/**
 * Hand Scanner 5000
 *
 * Simulated hand scanner 
 * for E's 3rd Grade Class
 */
#include <Arduino.h>
#include "bsp.h"
#include "sound_controller.h"

LED driver snippet: https://gist.github.com/chadpaulson/1834442

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

  //temp setup of rgb
  configureLED(RED_LED);
  configureLED(GREEN_LED);
  configureLED(BLUE_LED);

  //Test Sound
  soundTest();
}

//=========================================================
//- Loop
//-  main control loop for arduino
//=========================================================
void loop() 
{
  // run heartbeat
  heartbeat();

  turnOffLED(GREEN_LED);
  turnOffLED(BLUE_LED);
  turnOffLED(RED_LED);
  //delay(500);
  
  turnOnLED(RED_LED);
  turnOnLED(BLUE_LED);
  delay(500);  

  turnOffLED(GREEN_LED);
  turnOffLED(BLUE_LED);
  turnOffLED(RED_LED);
  //delay(500);
  
  turnOnLED(RED_LED);
  turnOnLED(GREEN_LED);
  delay(500);  

  turnOffLED(GREEN_LED);
  turnOffLED(BLUE_LED);
  turnOffLED(RED_LED);
  //delay(500);
  
  turnOnLED(GREEN_LED);
  turnOnLED(BLUE_LED);
  delay(500);  

  Serial.println("Test Console");
}