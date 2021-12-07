/* 
  Adapted from:
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#ifndef _JINGLE_BELLS_H_
#define _JINGLE_BELLS_H_

#include "notes.h"

namespace JingleBells
{
        // change this to make the song slower or faster
        int tempo = 300;

        // notes of the moledy followed by the duration.
        // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
        // !!negative numbers are used to represent dotted notes,
        // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
        int melody[] = {

        NOTE_E4, 2, NOTE_E4, 2, NOTE_E4, -4, REST, 4, 
        NOTE_E4, 2, NOTE_E4, 2, NOTE_E4, -4, REST, 4, 
        NOTE_E4, 2, NOTE_G4, 2, NOTE_C4, -4, NOTE_D4, 4, NOTE_E4, -4, REST, -8,

        NOTE_F4, 2, NOTE_F4, 2, NOTE_F4, -4, REST, 0, 
        NOTE_F4, 4, NOTE_F4, 2, NOTE_E4, 2, NOTE_E4, 2, REST, 0, 

        NOTE_E4, 4, NOTE_E4, 4, NOTE_G4, 2, NOTE_G4, 2, NOTE_F4, 2, NOTE_D4, 2, NOTE_C4, -8, REST, -8, 
        };
}

#endif