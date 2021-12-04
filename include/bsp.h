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
#define KEYPAD_INT_PIN D0
#define KEYPAD_LED_1 14
#define KEYPAD_LED_2 13
#define KEYPAD_LED_3 12



//=========================================================
//- Hand Scanner Lights
//=========================================================



#define RED_LED D2
#define BLUE_LED D3
#define GREEN_LED D4


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


#endif