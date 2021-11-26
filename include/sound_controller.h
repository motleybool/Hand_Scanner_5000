/**
 * Sound Controller
 *
 * This class controls onboard sound
 */
#include <Arduino.h>
#include "bsp.h"


//=========================================================
//- SoundTest Function
//-  tests the buzzer functionality
//=========================================================
class SoundController 
{
  private:
    //- Private vars
    int width, height;

  public:
    //=========================================================
    //- Constructor
    //=========================================================
    SoundController(int buzzer_pin);

    //=========================================================
    //- SoundTest Function
    //-  tests the buzzer functionality
    //=========================================================
    void soundTest(void);
};
