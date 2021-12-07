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
  //pIO->pinMode(LED_1, ANALOG_OUTPUT);
  pIO->pinMode(LED_1, OUTPUT);
  LED_2 = led_2_pin;
  //pIO->pinMode(LED_2, ANALOG_OUTPUT);
  pIO->pinMode(LED_2, OUTPUT);
  LED_3 = led_3_pin;
  //pIO->pinMode(LED_3, ANALOG_OUTPUT);
  pIO->pinMode(LED_3, OUTPUT);

  //Initialize Keypad Engine

  // Sleep time range: 128 ms - 8192 ms (powers of 2) 0=OFF
  unsigned int sleepTime = 0;

  // Scan time range: 1-128 ms, powers of 2
  byte scanTime = 16; // Scan time per row, in ms
  
  // Debounce time range: 0.5 - 64 ms (powers of 2)
  byte debounceTime = 8; // Debounce time

  // Initialize Keypad
  pIO->keypad(KEY_ROWS, KEY_COLS, sleepTime, scanTime, debounceTime);

  //Reset code
  resetController();

  Serial.println("Keypad Controller Initialized...");
}
void KeypadController::resetController(void)
{
  Serial.println("Reseting Controller...");

  //Shutoff LEDs
  pIO->digitalWrite(LED_1, HIGH);
  pIO->digitalWrite(LED_2, HIGH);
  pIO->digitalWrite(LED_3, HIGH);

  //Clear out code
  key_code.code[0] = -1;
  key_code.code[1] = -1;
  key_code.code[2] = -1;
  key_code.index = 0;
}

  //=========================================================
  //- registerKeypress Function
  //-  checks for and fetches key value
  //-  returns true if sequence is complete
  //=========================================================
  CODE_TYPE KeypadController::registerKeypress(void)
  {
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
        int val = keyValue[row][col];
        Serial.print(String(row) + " | " + String(col) + " | ");
        Serial.println(key);
        Serial.printf("value - %d\n", val);

        //Save to code store
        key_code.code[key_code.index] = val;
        key_code.index++;

        //Process Code Step
        if(key_code.index == 1) {
          breathLED(LED_1);
        }
        else if(key_code.index == 2) {
          breathLED(LED_2);
        }
        else if(key_code.index == 3) {
          breathLED(LED_3);

          //display code and reset
          Serial.printf("Full code: %d-%d-%d\n", key_code.code[0], key_code.code[1], key_code.code[2]);

          //Evaluate Code
          return evaluateCode();
        }
    }

    return CODE_TYPE::CODE_IMPCOMPLETE;
  }

//=========================================================
//- LED Convience Functions
//=========================================================
void KeypadController::breathLED(int led)
{
  //pIO->breathe(led, 1000, 500, 500, 250);
  pIO->blink(led, 500, 250, 255, 0);
}
void KeypadController::turnOnLED(int led)
{
  pIO->digitalWrite(led, LOW);
  //pIO->breathe(led, 1, 0, 0, 0);
}
void KeypadController::turnOffLED(int led)
{
  pIO->digitalWrite(led, HIGH);
  //pIO->breathe(led, 0, 1, 0, 0);
}

//=========================================================
//- Evaluate Code Input
//=========================================================
CODE_TYPE KeypadController::evaluateCode(void)
{
    //Valid Florida Code
    if(key_code.code[0] == FL_1 && key_code.code[1] == FL_2 && key_code.code[2] == FL_3)
    {
      return CODE_TYPE::VALID_CODE;
    }
    //Valid Maine Code
    else if(key_code.code[0] == Maine_1 && key_code.code[1] == Maine_2 && key_code.code[2] == Maine_3)
    {
      return CODE_TYPE::VALID_CODE;
    }
    //Light Sensor Code
    else if(key_code.code[0] == SOFF_1 && key_code.code[1] == SOFF_2 && key_code.code[2] == SOFF_3)
    {
      return CODE_TYPE::TURN_OFF_SENSOR;
    }
    //XMas Code
    else if(key_code.code[0] == XMas_1 && key_code.code[1] == XMas_2 && key_code.code[2] == XMas_3)
    {
      return CODE_TYPE::XMAS_TIME;
    }
    //Imperial Code
    else if(key_code.code[0] == IM_1 && key_code.code[1] == IM_2 && key_code.code[2] == IM_3)
    {
      return CODE_TYPE::ORDER_66;
    }
    else {
      return CODE_TYPE::INVALID_CODE;
    }
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
