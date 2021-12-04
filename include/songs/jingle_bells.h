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
        int tempo = 150;

        // notes of the moledy followed by the duration.
        // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
        // !!negative numbers are used to represent dotted notes,
        // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
        int melody[] = {

//  E, E, E,R,
//  E, E, E,R,
//  E, G, C, D, E, R,
//  f, f, f,f, f, E, E,E, E, D ,D,E, D, R, G ,R,

//  E, E, E,R,
//  E, E, E,R,
//  E, G, C, D, E, R,
//  f, f, f,f, f, E, E, E,  G,G, f, D, C,R

        NOTE_E4, 4, REST, 4, NOTE_E4, 4, REST, 4, NOTE_E4, 4, REST, 4, 
        NOTE_E4, 4, REST, 4, NOTE_E4, 4, REST, 4, NOTE_E4, 4, REST, 4, 
        NOTE_E4, 4, NOTE_G4, 4, NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4, REST, 4,

        NOTE_F4, 4, NOTE_F4, 4, NOTE_F4, 8, NOTE_F4, 4, NOTE_E4, 4, NOTE_E4, 8, NOTE_E4, 4, NOTE_E4, 4,
        NOTE_D4, 4, NOTE_D4, 8, NOTE_E4, 4, NOTE_D4, 4, REST, 4, NOTE_G4, 4, REST, 4,  

        NOTE_E4, 4, REST, 4, NOTE_E4, 4, REST, 4, NOTE_E4, 4, REST, 4, 
        NOTE_E4, 4, REST, 4, NOTE_E4, 4, REST, 4, NOTE_E4, 4, REST, 4, 
        NOTE_E4, 4, NOTE_G4, 4, NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4, REST, 4,

        NOTE_F4, 4, NOTE_F4, 4, NOTE_F4, 8, NOTE_F4, 4, NOTE_E4, 4, NOTE_E4, 4, NOTE_E4, 2, NOTE_G4, 8, NOTE_G4, 4, 
        NOTE_F4, 4, NOTE_D4, 4, NOTE_C4, 4, REST, 4,
    };
}

#endif