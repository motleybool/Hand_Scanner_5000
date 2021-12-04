/* 
  Adapted from:
  Imperial March - Star Wars
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#ifndef _IMPERIAL_MARCH_H_
#define _IMPERIAL_MARCH_H_

#include "notes.h"

namespace ImperialMarch
{
    // change this to make the song slower or faster
    int tempo = 120;

    // notes of the moledy followed by the duration.
    // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
    // !!negative numbers are used to represent dotted notes,
    // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
    int melody[] = {
      
      // Dart Vader theme (Imperial March) - Star wars 
      // Score available at https://musescore.com/user/202909/scores/1141521
      // The tenor saxophone part was used
      
      NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
      NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
      NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16,

      NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,//4
      NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
      NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
      
      NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
      NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

      NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
      NOTE_C5,4, NOTE_A4,-8, NOTE_C5,16, NOTE_E5,2,

      NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
      NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

      NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
      NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
      
    };
}

#endif