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
#define SC_LED_3_RED   10
#define SC_LED_3_GREEN 9
#define SC_LED_3_BLUE  8
// LED 4 - LRC
#define SC_LED_4_RED   15
#define SC_LED_4_GREEN 14
#define SC_LED_4_BLUE  13

#define LIGHT_SENSOR_PIN A0

//=========================================================
//- Codes
//=========================================================
//- Imperial March *-6-6
#define IM_1 55
#define IM_2 6
#define IM_3 6
//- XMas *-2-5
#define XMas_1 55
#define XMas_2 2
#define XMas_3 5
//- Light Sensor Off *-9-9
#define SOFF_1 55
#define SOFF_2 9
#define SOFF_3 9
//- Valid Florida 4-0-7
#define FL_1 4
#define FL_2 0
#define FL_3 7
//- Valid Maine 8-8-2
#define Maine_1 8
#define Maine_2 8
#define Maine_3 2

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