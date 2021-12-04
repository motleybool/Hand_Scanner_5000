/**
 * Keypad Controller
 *
 * This class controls the
 * Keypad functions
 */
#include <Arduino.h>
#include "bsp.h"
#include <SparkFunSX1509.h> // Include SX1509 library

//-Constants
#define KEY_ROWS 4
#define KEY_COLS 3

//=========================================================
//- Keypad Function
//-  Keypad controller class
//=========================================================
class KeypadController 
{
  private:
    SX1509 *pIO;
    int LED_1;
    int LED_2;
    int LED_3;
    int INTERUPT;
    unsigned int sleepTime;
    byte scanTime;
    byte debounceTime;

    // Handy array we'll use to map row/column pairs to 
    // character values:
    const char keyMap[KEY_ROWS][KEY_COLS] = {
                                            {'1', '2', '3'},
                                            {'4', '5', '6'},
                                            {'7', '8', '9'},
                                            {'*', '0', '#'}};
    const int keyValue[KEY_ROWS][KEY_COLS] = {
                                            {1, 2, 3},
                                            {4, 5, 6},
                                            {7, 8, 9},
                                            {55, 0, 99}};
    
    
  public:
    //=========================================================
    //- Constructor
    //=========================================================
    KeypadController(int gpio_exp_addr, int led_1_pin, int led_2_pin, int led_3_pin, int int_pin);

    //=========================================================
    //- keypadTest Function
    //-  tests the keypad functionality
    //=========================================================
    void keypadTest(void);

    //=========================================================
    //- setPinCode Function
    //-  sets the pin code value
    //=========================================================
    void setPinCode(void);

    //=========================================================
    //- registerKeypress Function
    //-  checks for and fetches key value
    //-  returns true if sequence is complete
    //=========================================================
    bool registerKeypress(void);



};
