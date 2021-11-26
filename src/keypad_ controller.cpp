/**
 * Keypad Controller
 *
 * This class controls the
 * Keypad functions
 */
#include "keypad_controller.h"
#include <SparkFunSX1509.h> // Include SX1509 library

#define INT_PIN D0
const byte SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
#define KEY_ROWS 4
#define KEY_COLS 3

#define TEST_LED_PIN 5

SX1509 io; // Create an SX1509 object

// Handy array we'll use to map row/column pairs to 
// character values:
char keyMap[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}};

void setup_keypad(void)
{
  if (!io.begin(SX1509_ADDRESS))
  {
    Serial.println("Failed to communicate.");
    while (1)
      ;
  }

  delay(1000);

  io.pinMode(TEST_LED_PIN, ANALOG_OUTPUT);
  //io.digitalWrite(TEST_LED_PIN, LOW);
  io.breathe(TEST_LED_PIN, 1000, 500, 500, 250);
  

  // To initialize the keypad engine, you at least need
  // to tell it how many rows and columns are in the matrix.
  // io.keypad(KEY_ROWS, KEY_COLS);
  // You can customize the keypad behavior further, by
  // defining scan time, debounce time, and sleep time:
  // Sleep time range: 128 ms - 8192 ms (powers of 2) 0=OFF
  unsigned int sleepTime = 0;
  // Scan time range: 1-128 ms, powers of 2
  byte scanTime = 16; // Scan time per row, in ms
  // Debounce time range: 0.5 - 64 ms (powers of 2)
  byte debounceTime = 8; // Debounce time
  io.keypad(KEY_ROWS, KEY_COLS, sleepTime, scanTime, debounceTime);

    // Set the ARDUINO pin as an input, to monitor the interrupt
  pinMode(INT_PIN, INPUT_PULLUP);
  Serial.println("Row | Col | Key");
}

void test_keypad(void)
{
    // If the interrupt pin goes active-low, a keypad button
    // is begin pressed:
    if (!digitalRead(INT_PIN))
    {
        // Use readKeypad() to get a binary representation for
        // which row and column are pressed
        unsigned int keyData = io.readKeypad();

        // Use the getRow, and getCol helper functions to find
        // which row and column keyData says are active.
        byte row = io.getRow(keyData);
        byte col = io.getCol(keyData);
        char key = keyMap[row][col];
        Serial.print(String(row) + " | " + String(col) + " | ");
        Serial.println(key);
    }
}
