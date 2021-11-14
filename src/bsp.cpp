#include "Arduino.h"
#include "bsp.h"

//button functions
void configureButton(int pin, bool pullup)
{
    if(pullup) {
        pinMode(pin, INPUT_PULLUP);
    }
    else {
        pinMode(pin, INPUT);
    }
}
bool isButtonPressed(int pin, bool invert)
{
    bool check_high = invert ? LOW : HIGH;
    if(digitalRead(pin) == check_high) {
        return true;
    }
    else {
        return false;
    }
}

//LED functions
void configureLED(int pin)
{
    pinMode(pin, OUTPUT);
}
void turnOnLED(int pin)
{
    digitalWrite(pin, LOW);
}
void turnOffLED(int pin)
{
    digitalWrite(pin, HIGH);
}
void blinkLED(int pin, int blinks)
{
    for(int i=0; i<blinks; i++)
    {
        turnOnLED(pin);
        delay(BLINK_LED_ON);
        turnOffLED(pin);
        delay(BLINK_LED_OFF);
    }
}