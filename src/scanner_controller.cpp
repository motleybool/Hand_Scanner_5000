/**
 * Scanner Controller
 *
 * This class controls the
 * Hand Scanner functions
 */
#include "scanner_controller.h"


//=========================================================
//- Constructor
//=========================================================
ScannerController::ScannerController(int gpio_exp_addr, int sensor_pin, int led_1_red, int led_1_green, int led_1_blue, 
                                                                        int led_2_red, int led_2_green, int led_2_blue,
                                                                        int led_3_red, int led_3_green, int led_3_blue,
                                                                        int led_4_red, int led_4_green, int led_4_blue)
{
    //setup gpio expander
    pIO = new SX1509;
    if (!pIO->begin(gpio_exp_addr))
    {
        Serial.println("Failed to communicate.");
        while (1)
        ;
    }

    int PIN_MODE = ANALOG_OUTPUT;
    //setup rbg led 1
    LED_1.red = led_1_red;
    pIO->pinMode(LED_1.red, PIN_MODE);
    LED_1.green = led_1_green;
    pIO->pinMode(LED_1.green, PIN_MODE);
    LED_1.blue = led_1_blue;
    pIO->pinMode(LED_1.blue, PIN_MODE);

    //setup rbg led 2
    LED_2.red = led_2_red;
    pIO->pinMode(LED_2.red, PIN_MODE);
    LED_2.green = led_2_green;
    pIO->pinMode(LED_2.green, PIN_MODE);
    LED_2.blue = led_2_blue;
    pIO->pinMode(LED_2.blue, PIN_MODE);
    
    //setup rbg led 3
    LED_3.red = led_3_red;
    pIO->pinMode(LED_3.red, PIN_MODE);
    LED_3.green = led_3_green;
    pIO->pinMode(LED_3.green, PIN_MODE);
    LED_3.blue = led_3_blue;
    pIO->pinMode(LED_3.blue, PIN_MODE);

    //setup rbg led 4
    LED_4.red = led_4_red;
    pIO->pinMode(LED_4.red, PIN_MODE);
    LED_4.green = led_4_green;
    pIO->pinMode(LED_4.green, PIN_MODE);
    LED_4.blue = led_4_blue;
    pIO->pinMode(LED_4.blue, PIN_MODE);

    //setup light sensor pin
    bypass_sensor = false;
    hand_present = false;
    LIGHT_SENSOR = sensor_pin;
    sesnor_threadhold = SENSOR_THRESH;
    delay(500);

    resetController();

    Serial.println("Scanner Controller Initialized...");
}
void ScannerController::resetController(void)
{
    //clear display
    clearDisplay();

    //Reset Thresholds
    sesnor_threadhold = SENSOR_THRESH;
    hand_present = false;
    background_reading = analogRead(LIGHT_SENSOR); //seed background value
}

//=========================================================
//- takeLightReading Function
//-  true if under threshold, false if over
//-  automatically adjusts background average
//=========================================================
bool ScannerController::takeLightReading(void)
{
    //take light reading
    int lightvalue = 0;
    lightvalue = analogRead(LIGHT_SENSOR);
    Serial.printf("Light Sesnsor: %d, Background Value: %d\n", lightvalue, background_reading);

    //if bypass set return true
    if(bypass_sensor)
    {
        Serial.println("Sensor Bypass...");
        return true;
    }
    //is this below threhold
    else if(background_reading - lightvalue > sesnor_threadhold )
    {
        hand_present = true;
        return true;
    }
    // otherwise update background
    else {
        background_reading = lightvalue;
    }

    return false;
}

//=========================================================
//- RGB LED Convience Functions
//=========================================================
void ScannerController::turnOff(int pin)
{
    //pIO->digitalWrite(pin, HIGH);
    pIO->analogWrite(pin, 0);
}
void ScannerController::turnOn(int pin)
{
    //pIO->digitalWrite(pin, LOW);
    pIO->analogWrite(pin, 255);
}
void ScannerController::turnOffLED(RGB led)
{
    turnOff(led.red);
    turnOff(led.green);
    turnOff(led.blue);
}
void ScannerController::turnOnLED(RGB led, LED_COLORS color)
{
    switch (color)
    {
    case LED_COLORS::RED:
        turnOn(led.red);
        turnOff(led.green);
        turnOff(led.blue);
        break;
    case LED_COLORS::GREEN:
        turnOff(led.red);
        turnOn(led.green);
        turnOff(led.blue);
        break;
    case LED_COLORS::BLUE:
        turnOff(led.red);
        turnOff(led.green);
        turnOn(led.blue);
        break;
    case LED_COLORS::YELLOW:
        turnOn(led.red);
        turnOn(led.green);
        turnOff(led.blue);
        break;
    case LED_COLORS::CYAN:
        turnOff(led.red);
        turnOn(led.green);
        turnOn(led.blue);
        break;
    case LED_COLORS::MAGENTA:
        turnOn(led.red);
        turnOff(led.green);
        turnOn(led.blue);
        break;
    case LED_COLORS::WHITE:
        turnOn(led.red);
        turnOn(led.green);
        turnOn(led.blue);
        break;
    default:
        turnOffLED(led);
        break;
    }
}
//breathing functions
void ScannerController::startBreathing(int pin)
{
    pIO->breathe(pin, 1000, 500, 500, 250);
    //pIO->setupBlink(pin, );
}
void ScannerController::stopBreathing(int pin)
{
    pIO->breathe(pin, 1000, 500, 500, 250, 0);
    //pIO->setupBlink(pin, );
}
void ScannerController::stopBreathingLED(RGB led)
{
    stopBreathing(led.red);
    stopBreathing(led.green);
    stopBreathing(led.blue);
}
void ScannerController::startBreathingLED(RGB led, LED_COLORS color)
{
    switch (color)
    {
    case LED_COLORS::RED:
        startBreathing(led.red);
        stopBreathing(led.green);
        stopBreathing(led.blue);
        break;
    case LED_COLORS::GREEN:
        stopBreathing(led.red);
        startBreathing(led.green);
        stopBreathing(led.blue);
        break;
    case LED_COLORS::BLUE:
        stopBreathing(led.red);
        stopBreathing(led.green);
        startBreathing(led.blue);
        break;
    case LED_COLORS::YELLOW:
        startBreathing(led.red);
        startBreathing(led.green);
        stopBreathing(led.blue);
        break;
    case LED_COLORS::CYAN:
        stopBreathing(led.red);
        startBreathing(led.green);
        startBreathing(led.blue);
        break;
    case LED_COLORS::MAGENTA:
        startBreathing(led.red);
        stopBreathing(led.green);
        startBreathing(led.blue);
        break;
    case LED_COLORS::WHITE:
        startBreathing(led.red);
        startBreathing(led.green);
        startBreathing(led.blue);
        break;
    default:
        stopBreathingLED(led);
        break;
    }
}

//display functions
void ScannerController::setDisplayColor(LED_COLORS color)
{
    turnOnLED(LED_1, color);
    turnOnLED(LED_2, color);
    turnOnLED(LED_3, color);
    turnOnLED(LED_4, color);
}
void ScannerController::blinkDisplay(LED_COLORS color, int count, int ton, int toff, LED_COLORS off_color)
{
    for(int rep=0; rep < count; rep++)
    {
        //Turn on
        turnOnLED(LED_1, color);
        turnOnLED(LED_2, color);
        turnOnLED(LED_3, color);
        turnOnLED(LED_4, color);
        delay(ton);

        if(off_color == LED_COLORS::OFF)
        {
            //Turn Off
            turnOffLED(LED_1);
            turnOffLED(LED_2);
            turnOffLED(LED_3);
            turnOffLED(LED_4);
        }
        else {
            //Set Off Color
            turnOnLED(LED_1, off_color);
            turnOnLED(LED_2, off_color);
            turnOnLED(LED_3, off_color);
            turnOnLED(LED_4, off_color);
        }
        delay(toff);
    }
}
void ScannerController::breathDisplay(LED_COLORS bColor, LED_COLORS sColor)
{
    turnOnLED(LED_1, sColor);
    startBreathingLED(LED_2, bColor);
    turnOnLED(LED_3, sColor);
    startBreathingLED(LED_4, bColor);
}
void ScannerController::clearDisplay(void)
{
    turnOffLED(LED_1);
    turnOffLED(LED_2);
    turnOffLED(LED_3);
    turnOffLED(LED_4);
}

//=========================================================
//- toggleLightSensor Function
//-  turns off usage of the light sensor
//=========================================================
void ScannerController::toggleLightSensor(void)
{
    bypass_sensor = !bypass_sensor;
}

//=========================================================
//- Hand Present Functions
//-  checks for hand on scanner
//=========================================================
bool ScannerController::isHandPresent(void)
{
    //override if set
    if(bypass_sensor) {
        Serial.println("Hand Sensor Bypass...");
        return true;
    }
    //else if hand already present
    else if(hand_present) {
        return hand_present;
    }
    //else take reading
    else {
        return takeLightReading();
    }
}
void ScannerController::clearHandPresent(void)
{
    hand_present = false;
}

//=========================================================
//- scannerTest Function
//-  tests the scanner functionality
//=========================================================
void ScannerController::scannerTest(void)
{
    //Static Display Check
    // setDisplayColor(LED_COLORS::RED);
    // delay(500);
    // setDisplayColor(LED_COLORS::GREEN);
    // delay(500);
    // setDisplayColor(LED_COLORS::BLUE);
    // delay(500);
    // setDisplayColor(LED_COLORS::YELLOW);
    // delay(500);
    // setDisplayColor(LED_COLORS::CYAN);
    // delay(500);
    // setDisplayColor(LED_COLORS::MAGENTA);
    // delay(500);
    // setDisplayColor(LED_COLORS::WHITE);
    // delay(500);
    // clearDisplay();
    // delay(500);

    //Blink Display Check
    // blinkDisplay(LED_COLORS::RED, 3, 200, 100);
    // delay(500);
    // blinkDisplay(LED_COLORS::GREEN, 3, 200, 100);
    // delay(500);
    // blinkDisplay(LED_COLORS::BLUE, 3, 200, 100);
    // delay(500);
    // blinkDisplay(LED_COLORS::YELLOW, 3, 200, 100);
    // delay(500);
    // blinkDisplay(LED_COLORS::CYAN, 3, 200, 100);
    // delay(500);
    // blinkDisplay(LED_COLORS::MAGENTA, 3, 200, 100);
    // delay(500);
    // blinkDisplay(LED_COLORS::WHITE, 3, 200, 100);
    // delay(500);
    // blinkDisplay(LED_COLORS::BLUE, 3, 200, 100, LED_COLORS::YELLOW);
    // delay(500);
    // clearDisplay();
    // delay(500);

    //Breath Display Check
    clearDisplay();
    breathDisplay(LED_COLORS::RED, LED_COLORS::RED);
    delay(5000);
    clearDisplay();
    breathDisplay(LED_COLORS::GREEN, LED_COLORS::GREEN);
    delay(5000);
    clearDisplay();
    breathDisplay(LED_COLORS::BLUE, LED_COLORS::BLUE);
    delay(5000);
    clearDisplay();
    breathDisplay(LED_COLORS::YELLOW, LED_COLORS::YELLOW);
    delay(5000);
    clearDisplay();
    breathDisplay(LED_COLORS::CYAN, LED_COLORS::CYAN);
    delay(5000);
    clearDisplay();
    breathDisplay(LED_COLORS::MAGENTA, LED_COLORS::MAGENTA);
    delay(5000);
    clearDisplay();
    breathDisplay(LED_COLORS::WHITE, LED_COLORS::WHITE);
    delay(5000);
    clearDisplay();
    breathDisplay(LED_COLORS::RED, LED_COLORS::GREEN);
    delay(5000);
    clearDisplay();
    delay(2500);

    //setDisplayColor(LED_COLORS::WHITE);
}

void ScannerController::lightSensorTest(void)
{
    //test light sensor
    if(takeLightReading()) {
        Serial.println("Sensor Reading: Hand on Scanner");
        animationReady();
    }
    else {
        Serial.println("Sensor Reading: Hand off Scanner");
        clearDisplay();
    }
}

//=========================================================
//- animation Functions
//-  animations for scanner leds
//=========================================================
void ScannerController::animationIdle(void)
{
    breathDisplay(LED_COLORS::WHITE, LED_COLORS::WHITE);
}
void ScannerController::animationReady(void)
{
    setDisplayColor(LED_COLORS::CYAN);
}
void ScannerController::animationScanning(void)
{
    int step = 75;
    clearDisplay();

    setDisplayColor(LED_COLORS::CYAN);
    for(int i=0; i<4; i++)
    {
        turnOnLED(LED_1, LED_COLORS::BLUE);
        delay(step);
        turnOnLED(LED_2, LED_COLORS::BLUE);
        delay(step);
        turnOnLED(LED_3, LED_COLORS::BLUE);
        delay(step);
        turnOnLED(LED_4, LED_COLORS::BLUE);
        delay(step);
        turnOnLED(LED_1, LED_COLORS::MAGENTA);
        delay(step);
        turnOnLED(LED_2, LED_COLORS::MAGENTA);
        delay(step);
        turnOnLED(LED_3, LED_COLORS::MAGENTA);
        delay(step);
        turnOnLED(LED_4, LED_COLORS::MAGENTA);
        delay(step);
        turnOnLED(LED_1, LED_COLORS::YELLOW);
        delay(step);
        turnOnLED(LED_2, LED_COLORS::YELLOW);
        delay(step);
        turnOnLED(LED_3, LED_COLORS::YELLOW);
        delay(step);
        turnOnLED(LED_4, LED_COLORS::YELLOW);
        delay(step);
    }
}
void ScannerController::animationValidated(void)
{
    blinkDisplay(LED_COLORS::GREEN, 2, 200, 100);
    setDisplayColor(LED_COLORS::GREEN);
}
void ScannerController::animationInvalidated(void)
{
    blinkDisplay(LED_COLORS::RED, 2, 200, 100);
    setDisplayColor(LED_COLORS::RED);
}
void ScannerController::animationSensorOff(void)
{
    blinkDisplay(LED_COLORS::YELLOW, 2, 200, 100);
}
void ScannerController::animationXmas(void)
{
    clearDisplay();
    //breathDisplay(LED_COLORS::RED, LED_COLORS::GREEN);
    turnOnLED(LED_1, LED_COLORS::RED);
    turnOnLED(LED_2, LED_COLORS::GREEN);
    turnOnLED(LED_3, LED_COLORS::RED);
    turnOnLED(LED_4, LED_COLORS::GREEN);
}
void ScannerController::animationOrder66(void)
{
    clearDisplay();
    //breathDisplay(LED_COLORS::RED, LED_COLORS::RED);
    blinkDisplay(LED_COLORS::RED, 2, 100, 50);
    setDisplayColor(LED_COLORS::RED);
}