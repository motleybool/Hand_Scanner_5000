/* 
  Adapted from:
  Nokia Tune
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#ifndef _NOKIA_H_
#define _NOKIA_H_

#include "notes.h"

namespace Nokia
{
    // change this to make the song slower or faster
    int tempo = 180;

    // notes of the moledy followed by the duration.
    // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
    // !!negative numbers are used to represent dotted notes,
    // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
    int melody[] = {

    // Nokia Ringtone 
    // Score available at https://musescore.com/user/29944637/scores/5266155
    
    NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
    NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
    NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
    NOTE_A4, 2, 
    };
}

#endif