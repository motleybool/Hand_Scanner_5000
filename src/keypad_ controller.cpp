/**
 * Keypad Controller
 *
 * This class controls the
 * Keypad functions
 */
#include "keypad_controller.h"



//=========================================================
//- Constructor
//=========================================================
KeypadController::KeypadController(int gpio_exp_addr, int led_1_pin, int led_2_pin, int led_3_pin, int int_pin)
{
  //set interupt pin
  INTERUPT = int_pin;
  pinMode(INTERUPT, INPUT_PULLUP);

  //setup gpio expander
  pIO = new SX1509;
  if (!pIO->begin(gpio_exp_addr))
  {
    Serial.println("Failed to communicate.");
    while (1)
      ;
  }
  
  //setup led pins
  LED_1 = led_1_pin;
  pIO->pinMode(LED_1, ANALOG_OUTPUT);
  LED_2 = led_2_pin;
  pIO->pinMode(LED_2, ANALOG_OUTPUT);
  LED_3 = led_3_pin;
  pIO->pinMode(LED_3, ANALOG_OUTPUT);

  //Initialize Keypad Engine

  // Sleep time range: 128 ms - 8192 ms (powers of 2) 0=OFF
  unsigned int sleepTime = 0;

  // Scan time range: 1-128 ms, powers of 2
  byte scanTime = 16; // Scan time per row, in ms
  
  // Debounce time range: 0.5 - 64 ms (powers of 2)
  byte debounceTime = 8; // Debounce time

  // Initialize Keypad
  pIO->keypad(KEY_ROWS, KEY_COLS, sleepTime, scanTime, debounceTime);

  Serial.println("Keypad Controller Initialized...");
}

//=========================================================
//- keypadTest Function
//-  tests the keypad functionality
//=========================================================
void KeypadController::keypadTest(void)
{
  //test breath the LEDs
  pIO->breathe(LED_1, 1000, 500, 500, 250);
  pIO->breathe(LED_2, 1000, 500, 500, 250);
  pIO->breathe(LED_3, 1000, 500, 500, 250);

  // If the interrupt pin goes active-low, a keypad button
  // is begin pressed:
  if (!digitalRead(INTERUPT))
  {
      // Use readKeypad() to get a binary representation for
      // which row and column are pressed
      unsigned int keyData = pIO->readKeypad();

      // Use the getRow, and getCol helper functions to find
      // which row and column keyData says are active.
      byte row = pIO->getRow(keyData);
      byte col = pIO->getCol(keyData);
      char key = keyMap[row][col];
      Serial.print(String(row) + " | " + String(col) + " | ");
      Serial.println(key);
  }
}
