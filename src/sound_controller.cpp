/**
 * Sound Controller
 *
 * This class controls onboard sound
 */
#include "sound_controller.h"



SoundController::SoundController(int buzzer_pin)
{
  //Do Init
}



#define buzzerPin D6 // output pin for buzzer
//https://github.com/robsoncouto/arduino-songs

const int songLength = 18; // number of notes in the buzzer song
char notes[] = "e e e e e e egcde "; // notes and rests of the buzzer song
float beats[] = {1,0.2,1,0.2,2,0.2,1,0.2,1,0.2,2,0.2,1,1,1,1,4,1}; // length of each note and rest in the buzzer song
int tempo = 150; // speed of the buzzer song

int frequency(char note) 
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.

  int i;
  const int numNotes = 8;  // number of notes we're storing

  // The following arrays hold the note characters and their
  // corresponding frequencies. The last "C" note is uppercase
  // to separate it from the first lowercase "c". If you want to
  // add more notes, you'll need to use unique characters.

  // For the "char" (character) type, we put single characters
  // in single quotes.

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
  /*
  note  frequency
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz
  */

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}



void soundTest(void)
{
 pinMode(buzzerPin, OUTPUT); // setting the buzzer control pin to an output on the board

  int i = 0; // counter for the buzzer song
  int duration; // value for the duration of the buzzer song

    // This for loop reads the buzzer song
      for (i = 0; i < songLength; i++) // step through the song arrays
      {
        duration = beats[i] * tempo; // length of note/rest in ms

        if (notes[i] == ' ') // is this a rest?         
        {
          delay(duration);  // then pause for a moment         
        }
        else // otherwise, play the note                       
        {
          tone(buzzerPin, frequency(notes[i]), duration); 
          delay(duration);    // wait for tone to finish        
        }
        delay(tempo/10);     // brief pause between notes   
      }



}

