/**
 * Sound Controller
 *
 * This class controls onboard sound
 */
#include <Arduino.h>
#include "bsp.h"


class SoundController 
{
  private:
    int width, height;
  public:
    void set_values (int,int);
    int area (void);
}


//=========================================================
//- SoundTest Function
//-  tests the buzzer functionality
//=========================================================
void soundTest(void);