//- Header defines for board convience functions

#ifndef _BSP_H_
#define _BSP_H_


//PIN Definitions
#define ONBOARD_LED D0 // Led in NodeMCU at pin GPIO16 (D0)

//=========================================================
//- Buzzer Hardware
//=========================================================
#define BUZZER_PIN D6

//=========================================================
//- Keypad Hardware
//=========================================================
const byte KEYPAD_ADDRESS = 0x3E;  // SX1509 I2C address (00)
#define KEYPAD_INT_PIN D4
#define KEYPAD_LED_1 14
#define KEYPAD_LED_2 13
#define KEYPAD_LED_3 12

//=========================================================
//- Hand Scanner Lights
//=========================================================
const byte SCANNER_ADDRESS = 0x3F;  // SX1509 I2C address (00)

// LED 1 - ULC
#define SC_LED_1_RED   1
#define SC_LED_1_GREEN 2
#define SC_LED_1_BLUE  3
// LED 2 - URC
#define SC_LED_2_RED   5
#define SC_LED_2_GREEN 6
#define SC_LED_2_BLUE  7
// LED 3 - LLC
#define SC_LED_3_RED   15
#define SC_LED_3_GREEN 14
#define SC_LED_3_BLUE  13
// LED 4 - LRC
#define SC_LED_4_RED   10
#define SC_LED_4_GREEN 9
#define SC_LED_4_BLUE  8

#define LIGHT_SENSOR_PIN A0

//=========================================================
//- LED Common Functions
//=========================================================

//constants
static const unsigned int BLINK_LED_ON = 200;
static const unsigned int BLINK_LED_OFF = 100;

//button functions
void configureButton(int pin, bool pullup = true);
bool isButtonPressed(int pin, bool invert = false);

//LED functions
void configureLED(int pin);
void turnOnLED(int pin);
void turnOffLED(int pin);
void blinkLED(int pin, int blinks = 1);

//RGB LED Structure
struct RGB {
    int red;
    int green;
    int blue;
};


#endif