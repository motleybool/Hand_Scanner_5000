/**
 * Sound Controller
 *
 * This class controls onboard sound
 * 
 * Credit to the awesome library by Robson Couto
 * found here: https://github.com/robsoncouto/arduino-songs
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
    int buzzer;
    
  public:
    //=========================================================
    //- Constructor
    //=========================================================
    SoundController(int buzzer_pin);

    //Songs
    enum Song {Nokia, Starwars, Imperial, Jinglebells, Fail};
    enum SoundFX {Failure, Succeed, OneUp, Fireball, Coin};

    //=========================================================
    //- SoundTest Function
    //-  tests the buzzer functionality
    //=========================================================
    void soundTest(void);

    //=========================================================
    //- playSong Function
    //-  plays the song on the buzzer
    //=========================================================
    void playSong(Song song);

    //=========================================================
    //- playSoundFX Function
    //-  plays the souund fx on the buzzer
    //=========================================================
    void playSoundFX(SoundFX fx);
};
