/* 
  Adapted from:
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#ifndef _FAIL_H_
#define _FAIL_H_

#include "notes.h"

namespace Failure
{
    // change this to make the song slower or faster
    int tempo = 180;

    // notes of the moledy followed by the duration.
    // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
    // !!negative numbers are used to represent dotted notes,
    // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
    int melody[] = {

        NOTE_E5, 16, NOTE_D5, 16

    };
}

#endif