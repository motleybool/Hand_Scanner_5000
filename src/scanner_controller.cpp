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

    //setup rbg led 1
    LED_1.red = led_1_red;
    pIO->pinMode(LED_1.red, ANALOG_OUTPUT);
    LED_1.green = led_1_green;
    pIO->pinMode(LED_1.green, ANALOG_OUTPUT);
    LED_1.blue = led_1_blue;
    pIO->pinMode(LED_1.blue, ANALOG_OUTPUT);

    //setup rbg led 2
    LED_2.red = led_2_red;
    pIO->pinMode(LED_2.red, ANALOG_OUTPUT);
    LED_2.green = led_2_green;
    pIO->pinMode(LED_2.green, ANALOG_OUTPUT);
    LED_2.blue = led_2_blue;
    pIO->pinMode(LED_2.blue, ANALOG_OUTPUT);
    
    //setup rbg led 3
    LED_3.red = led_3_red;
    pIO->pinMode(LED_3.red, ANALOG_OUTPUT);
    LED_3.green = led_3_green;
    pIO->pinMode(LED_3.green, ANALOG_OUTPUT);
    LED_3.blue = led_3_blue;
    pIO->pinMode(LED_3.blue, ANALOG_OUTPUT);

    //setup rbg led 4
    LED_4.red = led_4_red;
    pIO->pinMode(LED_4.red, ANALOG_OUTPUT);
    LED_4.green = led_4_green;
    pIO->pinMode(LED_4.green, ANALOG_OUTPUT);
    LED_4.blue = led_4_blue;
    pIO->pinMode(LED_4.blue, ANALOG_OUTPUT);

    //setup light sensor pin
    LIGHT_SENSOR = sensor_pin;
    sesnor_threadhold = SENSOR_THRESH;
    background_reading = analogRead(LIGHT_SENSOR); //seed background value

    Serial.println("Scanner Controller Initialized...");
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
    Serial.printf("Light Sesnsor: %d\n", lightvalue);
    Serial.printf("Background Value: %d\n", background_reading);

    //is this below threhold
    if(background_reading - lightvalue > sesnor_threadhold )
    {
        return true;
    }
    // otherwise update background
    else {
        background_reading = lightvalue;
    }

    return false;
}

//=========================================================
//- scannerTest Function
//-  tests the scanner functionality
//=========================================================
void ScannerController::scannerTest(void)
{
    pIO->digitalWrite(LED_1.red, HIGH);
    pIO->digitalWrite(LED_1.green, HIGH);
    pIO->digitalWrite(LED_1.blue, HIGH);
    pIO->digitalWrite(LED_2.red, HIGH);
    pIO->digitalWrite(LED_2.green, HIGH);
    pIO->digitalWrite(LED_2.blue, HIGH);
    pIO->digitalWrite(LED_3.red, HIGH);
    pIO->digitalWrite(LED_3.green, HIGH);
    pIO->digitalWrite(LED_3.blue, HIGH);
    pIO->digitalWrite(LED_4.red, HIGH);
    pIO->digitalWrite(LED_4.green, HIGH);
    pIO->digitalWrite(LED_4.blue, HIGH);
    
    RGB test = LED_1;
    //red
    pIO->digitalWrite(test.red, LOW);
    pIO->digitalWrite(test.green, HIGH);
    pIO->digitalWrite(test.blue, HIGH);
    delay(1000);
    //green
    pIO->digitalWrite(test.red, HIGH);
    pIO->digitalWrite(test.green, LOW);
    pIO->digitalWrite(test.blue, HIGH);
    delay(1000);
    //blue
    pIO->digitalWrite(test.red, HIGH);
    pIO->digitalWrite(test.green, HIGH);
    pIO->digitalWrite(test.blue, LOW);
    delay(1000);
    
    test = LED_2;
    //red
    pIO->digitalWrite(test.red, LOW);
    pIO->digitalWrite(test.green, HIGH);
    pIO->digitalWrite(test.blue, HIGH);
    delay(1000);
    //green
    pIO->digitalWrite(test.red, HIGH);
    pIO->digitalWrite(test.green, LOW);
    pIO->digitalWrite(test.blue, HIGH);
    delay(1000);
    //blue
    pIO->digitalWrite(test.red, HIGH);
    pIO->digitalWrite(test.green, HIGH);
    pIO->digitalWrite(test.blue, LOW);
    delay(1000);

    test = LED_3;
    //red
    pIO->digitalWrite(test.red, LOW);
    pIO->digitalWrite(test.green, HIGH);
    pIO->digitalWrite(test.blue, HIGH);
    delay(1000);
    //green
    pIO->digitalWrite(test.red, HIGH);
    pIO->digitalWrite(test.green, LOW);
    pIO->digitalWrite(test.blue, HIGH);
    delay(1000);
    //blue
    pIO->digitalWrite(test.red, HIGH);
    pIO->digitalWrite(test.green, HIGH);
    pIO->digitalWrite(test.blue, LOW);
    delay(1000);

    test = LED_4;
    //red
    pIO->digitalWrite(test.red, LOW);
    pIO->digitalWrite(test.green, HIGH);
    pIO->digitalWrite(test.blue, HIGH);
    delay(1000);
    //green
    pIO->digitalWrite(test.red, HIGH);
    pIO->digitalWrite(test.green, LOW);
    pIO->digitalWrite(test.blue, HIGH);
    delay(1000);
    //blue
    pIO->digitalWrite(test.red, HIGH);
    pIO->digitalWrite(test.green, HIGH);
    pIO->digitalWrite(test.blue, LOW);
    delay(1000);


    //test light sensor
    if(takeLightReading()) {
        Serial.println("Sensor Reading: Hand on Scanner");
    }
    else {
        Serial.println("Sensor Reading: Hand off Scanner");
    }
}

void ScannerController::lightSensorTest(void)
{

}
