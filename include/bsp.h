//- Header defines for board convience functions

//PIN Definitions
#define ONBOARD_LED D0 // Led in NodeMCU at pin GPIO16 (D0)


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
