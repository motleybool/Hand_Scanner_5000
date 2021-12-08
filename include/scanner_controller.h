/**
 * Scanner Controller
 *
 * This class controls the
 * Hand Scanner functions
 */
#include <Arduino.h>
#include "bsp.h"
#include <SparkFunSX1509.h> // Include SX1509 library

//LED driver snippet: https://gist.github.com/chadpaulson/1834442

//Sensor Threashold
#define SENSOR_THRESH 50

//=========================================================
//- Scanner Function
//-  Scanner controller class
//=========================================================
class ScannerController 
{
  private:
    SX1509 *pIO;
    RGB LED_1;
    RGB LED_2;
    RGB LED_3;
    RGB LED_4;
    enum LED_COLORS {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, OFF};
    
    // Light Sensor Settings
    int LIGHT_SENSOR;
    bool bypass_sensor;
    bool hand_present;
    int background_reading;
    int sesnor_threadhold;

    //=========================================================
    //- takeLightReading Function
    //-  true if under threshold, false if over
    //-  automatically adjusts background average
    //=========================================================
    bool takeLightReading(void);

    //=========================================================
    //- RGB LED Convience Functions
    //=========================================================
    void turnOff(int pin);
    void turnOn(int pin);
    void turnOffLED(RGB led);
    void turnOnLED(RGB led, LED_COLORS color);
    //breathing functions
    void startBreathing(int pin);
    void stopBreathing(int pin);
    void stopBreathingLED(RGB led);
    void startBreathingLED(RGB led, LED_COLORS color);
    //display functions
    void setDisplayColor(LED_COLORS color);
    void blinkDisplay(LED_COLORS color, int count, int ton, int toff, LED_COLORS off_color = LED_COLORS::OFF);
    void breathDisplay(LED_COLORS bColor, LED_COLORS sColors);

  public:
    //=========================================================
    //- Constructor
    //=========================================================
    ScannerController(int gpio_exp_addr, int sensor_pin, int led_1_red, int led_1_green, int led_1_blue, 
                                                         int led_2_red, int led_2_green, int led_2_blue,
                                                         int led_3_red, int led_3_green, int led_3_blue,
                                                         int led_4_red, int led_4_green, int led_4_blue);
    void resetController(void);

    //=========================================================
    //- toggleLightSensor Function
    //-  turns off usage of the light sensor
    //=========================================================
    void toggleLightSensor(void);

    //=========================================================
    //- Calibration Functions
    //-  helpers for calibration
    //=========================================================
    void setSensorThreshold(int thresh);
    int getSensorThreshold(void);
    int takeSensorSample(void);

    //=========================================================
    //- Hand Present Functions
    //-  checks for hand on scanner
    //=========================================================
    bool isHandPresent(void);
    void clearHandPresent(void);

    //=========================================================
    //- scannerTest Function
    //-  tests the scanner functionality
    //=========================================================
    void scannerTest(void);
    void lightSensorTest(void);

    //=========================================================
    //- animation Functions
    //-  animations for scanner leds
    //=========================================================
    void animationIdle(void);
    void animationReady(void);
    void animationScanning(void);
    void animationValidated(void);
    void animationInvalidated(void);
    void animationSensorOff(void);
    void animationCalibration(void);
    void animationCalibrationStep(void);
    void animationXmas(void);
    void animationOrder66(void);
    void animationCannon(void);
    void animationMario(void);
    void animationLion(void);
    void animationTetris(void);
    void clearDisplay(void);

};



