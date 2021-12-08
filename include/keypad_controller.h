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

//-Code Type
enum CODE_TYPE {
  CODE_IMPCOMPLETE,
  VALID_CODE,
  INVALID_CODE,
  TURN_OFF_SENSOR,
  CALIBRATION,
  XMAS_TIME,
  ORDER_66,
  LION,
  TETRIS,
  CANNON,
  MARIO,
};

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

    //Key Code
    struct KEY_CODE {
      int code[3];
      unsigned int index;
    } key_code;

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
    //=========================================================
    //- LED Convience Functions
    //=========================================================
    void breathLED(int led);
    void turnOnLED(int led);
    void turnOffLED(int led);

    //=========================================================
    //- Evaluate Code Input
    //=========================================================
    CODE_TYPE evaluateCode(void);
    
  public:
    //=========================================================
    //- Constructor
    //=========================================================
    KeypadController(int gpio_exp_addr, int led_1_pin, int led_2_pin, int led_3_pin, int int_pin);
    void resetController(void);

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
    CODE_TYPE registerKeypress(void);
    bool getKeyStroke(int *key_value);



};
