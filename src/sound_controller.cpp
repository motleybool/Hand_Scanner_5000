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
//-  plays the song on the buzzer
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
//- playSoundFX Function
//-  plays the souund fx on the buzzer
//=========================================================
void SoundController::playSoundFX(SoundFX fx)
{
  int NOTE_SUSTAIN = 250;

  Serial.println("Playing FX...");

  //Setup Fx
  switch (fx)
  {
  case SoundFX::Failure:
    tone(buzzer,NOTE_G4);
    delay(250);
    tone(buzzer,NOTE_C4);
    delay(500);
    noTone(buzzer);
    break;
  case SoundFX::Succeed:
    tone(buzzer,NOTE_A5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_B5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_C5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_B5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_C5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_D5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_C5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_D5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_E5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_D5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_E5);
    delay(NOTE_SUSTAIN);
    tone(buzzer,NOTE_E5);
    delay(NOTE_SUSTAIN);
    noTone(buzzer);
    break;
  case SoundFX::OneUp:
    tone(buzzer,NOTE_E6,125);
    delay(130);
    tone(buzzer,NOTE_G6,125);
    delay(130);
    tone(buzzer,NOTE_E7,125);
    delay(130);
    tone(buzzer,NOTE_C7,125);
    delay(130);
    tone(buzzer,NOTE_D7,125);
    delay(130);
    tone(buzzer,NOTE_G7,125);
    delay(125);
    noTone(buzzer);
    break;
  case SoundFX::Coin:
    tone(buzzer,NOTE_B5,100);
    delay(100);
    tone(buzzer,NOTE_E6,850);
    delay(800);
    noTone(buzzer);
    break;
  case SoundFX::Fireball:
    tone(buzzer,NOTE_G4,35);
    delay(35);
    tone(buzzer,NOTE_G5,35);
    delay(35);
    tone(buzzer,NOTE_G6,35);
    delay(35);
    noTone(buzzer);
    break;    

  //Default to failure tone
  default:
    tone(buzzer,NOTE_G4);
    delay(250);
    tone(buzzer,NOTE_C4);
    delay(500);
    noTone(buzzer);
    break;
  }

  Serial.println("FX Complete...");
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

