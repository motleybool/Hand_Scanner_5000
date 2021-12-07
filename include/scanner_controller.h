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
#define SENSOR_THRESH 25

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
    int LIGHT_SENSOR;
    
    // Light Sensor Settings
    bool use_light_sensor;
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
    void turnOffLED(RGB led);
    void turnOnRed(RGB led);
    void turnOnGreen(RGB led);
    void turnOnBlue(RGB led);
    void turnOnYellow(RGB led);
    void turnOnCyan(RGB led);
    void turnOnMagenta(RGB led);
    void turnOnWhite(RGB led);
    
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
    //- disableLightSensor Function
    //-  turns off usage of the light sensor
    //=========================================================
    void disableLightSensor(void);

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
    void animationScanning(void);
    void animationValidated(void);
    void animationInvalidated(void);
    void animationSensorOff(void);
    void animationXmas(void);
    void animationOrder66(void);

};



