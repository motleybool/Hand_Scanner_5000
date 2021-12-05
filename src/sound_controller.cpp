/**
 * Sound Controller
 *
 * This class controls onboard sound
 * 
 * Credit to the awesome library by Robson Couto
 * found here: https://github.com/robsoncouto/arduino-songs
 */
#include "sound_controller.h"
#include "songs/nokia.h"
#include "songs/imperial_march.h"
#include "songs/starwars_theme.h"
#include "songs/jingle_bells.h"
#include "songs/fail.h"

//=========================================================
//- Constructor
//=========================================================
SoundController::SoundController(int buzzer_pin)
{
  //Setup Buzzer Hardware
  buzzer = buzzer_pin;
}

//=========================================================
//- playSong Function
//-  plays the song passed on the buzzer
//=========================================================
void SoundController::playSong(Song song)
{
  //playback vars
  int* pmelody = 0; 
  int notes = 0;
  int wholenote = 0;
  int divider = 0;
  int noteDuration = 0;

  //Setup Song
  switch (song)
  {
  case Song::Nokia:
    pmelody = Nokia::melody;
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    notes = sizeof(Nokia::melody) / sizeof(Nokia::melody[0]) / 2;
    // this calculates the duration of a whole note in ms
    wholenote = (60000 * 4) / Nokia::tempo;
    break;
  case Song::Starwars:
    pmelody = StarWars::melody;
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    notes = sizeof(StarWars::melody) / sizeof(StarWars::melody[0]) / 2;
    // this calculates the duration of a whole note in ms
    wholenote = (60000 * 4) / StarWars::tempo;
    break;
  case Song::Imperial:
    pmelody = ImperialMarch::melody;
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    notes = sizeof(ImperialMarch::melody) / sizeof(ImperialMarch::melody[0]) / 2;
    // this calculates the duration of a whole note in ms
    wholenote = (60000 * 4) / ImperialMarch::tempo;
    break;
  case Song::Jinglebells:
    pmelody = JingleBells::melody;
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    notes = sizeof(JingleBells::melody) / sizeof(JingleBells::melody[0]) / 2;
    // this calculates the duration of a whole note in ms
    wholenote = (60000 * 4) / JingleBells::tempo;
    break;
  case Song::Fail:
    pmelody = Failure::melody;
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    notes = sizeof(Failure::melody) / sizeof(Failure::melody[0]) / 2;
    // this calculates the duration of a whole note in ms
    wholenote = (60000 * 4) / Failure::tempo;
    break;

  //Default to failure tone
  default:
    pmelody = Failure::melody;
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    notes = sizeof(Failure::melody) / sizeof(Failure::melody[0]) / 2;
    // this calculates the duration of a whole note in ms
    wholenote = (60000 * 4) / Failure::tempo;
    break;
  }

  Serial.println("Playing Song...");

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = pmelody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, pmelody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }

  Serial.println("Song Complete...");
}

//=========================================================
//- SoundTest Function
//-  tests the buzzer functionality
//=========================================================
void SoundController::soundTest(void)
{
  //implement test
  //playSong(Song::Imperial);
  playSong(Song::Jinglebells);
  playSong(Song::Nokia);
  //playSong(Song::Starwars);
  playSong(Song::Fail);
}



// #define buzzerPin D6 // output pin for buzzer
// //https://github.com/robsoncouto/arduino-songs

// const int songLength = 18; // number of notes in the buzzer song
// char notes[] = "e e e e e e egcde "; // notes and rests of the buzzer song
// float beats[] = {1,0.2,1,0.2,2,0.2,1,0.2,1,0.2,2,0.2,1,1,1,1,4,1}; // length of each note and rest in the buzzer song
// int tempo = 150; // speed of the buzzer song

// int frequency(char note) 
// {
//   // This function takes a note character (a-g), and returns the
//   // corresponding frequency in Hz for the tone() function.

//   int i;
//   const int numNotes = 8;  // number of notes we're storing

//   // The following arrays hold the note characters and their
//   // corresponding frequencies. The last "C" note is uppercase
//   // to separate it from the first lowercase "c". If you want to
//   // add more notes, you'll need to use unique characters.

//   // For the "char" (character) type, we put single characters
//   // in single quotes.

//   char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
//   int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
//   /*
//   note  frequency
//   c     262 Hz
//   d     294 Hz
//   e     330 Hz
//   f     349 Hz
//   g     392 Hz
//   a     440 Hz
//   b     494 Hz
//   C     523 Hz
//   */

//   // Now we'll search through the letters in the array, and if
//   // we find it, we'll return the frequency for that note.

//   for (i = 0; i < numNotes; i++)  // Step through the notes
//   {
//     if (names[i] == note)         // Is this the one?
//     {
//       return(frequencies[i]);     // Yes! Return the frequency
//     }
//   }
//   return(0);  // We looked through everything and didn't find it,
//               // but we still need to return a value, so return 0.
// }



// void soundTest(void)
// {
//  pinMode(buzzerPin, OUTPUT); // setting the buzzer control pin to an output on the board

//   int i = 0; // counter for the buzzer song
//   int duration; // value for the duration of the buzzer song

//     // This for loop reads the buzzer song
//       for (i = 0; i < songLength; i++) // step through the song arrays
//       {
//         duration = beats[i] * tempo; // length of note/rest in ms

//         if (notes[i] == ' ') // is this a rest?         
//         {
//           delay(duration);  // then pause for a moment         
//         }
//         else // otherwise, play the note                       
//         {
//           tone(buzzerPin, frequency(notes[i]), duration); 
//           delay(duration);    // wait for tone to finish        
//         }
//         delay(tempo/10);     // brief pause between notes   
//       }



// }

