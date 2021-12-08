/* 
  Adapted from:
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#ifndef _CANNON_H_
#define _CANNON_H_

#include "notes.h"

namespace CannonD
{
    // change this to make the song slower or faster
    int tempo = 100;

    // notes of the moledy followed by the duration.
    // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
    // !!negative numbers are used to represent dotted notes,
    // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
    int melody[] = {

        // Cannon in D - Pachelbel
        // Score available at https://musescore.com/user/4710311/scores/1975521
        // C F
        // NOTE_FS4,2, NOTE_E4,2,
        // NOTE_D4,2, NOTE_CS4,2,
        // NOTE_B3,2, NOTE_A3,2,
        // NOTE_B3,2, NOTE_CS4,2,
        // NOTE_FS4,2, NOTE_E4,2,
        // NOTE_D4,2, NOTE_CS4,2,
        // NOTE_B3,2, NOTE_A3,2,
        // NOTE_B3,2, NOTE_CS4,2,
        // NOTE_D4,2, NOTE_CS4,2,
        // NOTE_B3,2, NOTE_A3,2,
        // NOTE_G3,2, NOTE_FS3,2,
        // NOTE_G3,2, NOTE_A3,2,

        NOTE_D4,4, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,4, NOTE_FS4,8, NOTE_G4,8, 
        NOTE_A4,4, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, 
        NOTE_FS4,4, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,4, NOTE_FS3,8, NOTE_G3,8,
        NOTE_A3,8, NOTE_G3,8, NOTE_FS3,8, NOTE_G3,8, NOTE_A3,2,
        NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_G3,4, NOTE_FS3,8, NOTE_E3,8, 
        NOTE_FS3,4, NOTE_D3,8, NOTE_E3,8, NOTE_FS3,8, NOTE_G3,8, NOTE_A3,8, NOTE_B3,8,

        // NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_B3,4, NOTE_CS4,8, NOTE_D4,8,
        // NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,2,
        // NOTE_A4,4, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,4,
        // NOTE_FS4,8, NOTE_G4,8, NOTE_A4,8, NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8,
        // NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, NOTE_FS4,4, NOTE_D4,8, NOTE_E4,8,
        // NOTE_FS4,8, NOTE_CS4,8, NOTE_A3,8, NOTE_A3,8,

        // NOTE_CS4,4, NOTE_B3,4, NOTE_D4,8, NOTE_CS4,8, NOTE_B3,4,
        // NOTE_A3,8, NOTE_G3,8, NOTE_A3,4, NOTE_D3,8, NOTE_E3,8, NOTE_FS3,8, NOTE_G3,8,
        // NOTE_A3,8, NOTE_B3,4, NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_B3,4,
        // NOTE_CS4,8, NOTE_D4,8, NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8,
        // NOTE_FS4,8, NOTE_G4,8, NOTE_A4,2,  

    };
}

#endif