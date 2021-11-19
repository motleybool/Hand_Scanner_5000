/**
 * Scanner Controller
 *
 * This class controls the
 * Hand Scanner functions
 */
#include "scanner_controller.h"

void lightReading()
{
    int lightvalue = 0;

    lightvalue = analogRead(LIGHT_PIN);
    Serial.printf("Reading Sesnsor %d\n", lightvalue);
    delay(100);

    if(lightvalue < 50)
    {
        Serial.println("It is dark");
    }
    else {
        Serial.println("It is light");
    }
}