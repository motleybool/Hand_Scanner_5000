/**
 * Hand Scanner 5000
 *
 * Simulated hand scanner 
 * for E's 3rd Grade Class
 */
#include <Arduino.h>
#include "bsp.h"
#include "sound_controller.h"
#include "scanner_controller.h"
#include "keypad_controller.h"

//#define test_led D6

//Controller objects
SoundController* soundController;
ScannerController* scannerController;
KeypadController* keypadController;

//=========================================================
//- Heartbeat Function
//-  strobe the onboard LED to indicate active loop
//=========================================================
void heartbeat(void) 
{
    blinkLED(ONBOARD_LED, 2);
}

//=========================================================
//- System Test Function
//-  run through each controller's tests
//=========================================================
void system_test(void) 
{
  //Test Sound Controller
  //soundController->soundTest();

  //Test Keypad
  //keypadController->keypadTest();

  //Scanner Test
  //scannerController->scannerTest();
}

//=========================================================
//- Setup
//-  init routine for arduino
//=========================================================
void setup() 
{
  //setup serial monitor
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  //wait to connect serial monitor
  delay(5000);

  //setup sound controller
  soundController = new SoundController(BUZZER_PIN);

  //setup keypad controller
  keypadController = new KeypadController(KEYPAD_ADDRESS, KEYPAD_LED_1, KEYPAD_LED_2, KEYPAD_LED_3, KEYPAD_INT_PIN);

  //setup scanner controller
  scannerController = new ScannerController(SCANNER_ADDRESS, LIGHT_SENSOR_PIN, SC_LED_1_RED, SC_LED_1_GREEN, SC_LED_1_BLUE,
                                                                               SC_LED_2_RED, SC_LED_2_GREEN, SC_LED_2_BLUE,
                                                                               SC_LED_3_RED, SC_LED_3_GREEN, SC_LED_3_BLUE,
                                                                               SC_LED_4_RED, SC_LED_4_GREEN, SC_LED_4_BLUE);
}

//=========================================================
//- Loop
//-  main control loop for arduino
//=========================================================
void loop() 
{
  // run heartbeat
  heartbeat();

  // run tests
  //system_test();

  //Register Keystroke
  CODE_TYPE code = keypadController->registerKeypress();

  //Check for Full Code
  if(code != CODE_TYPE::CODE_IMPCOMPLETE)
  {
    //Start Scanning Animation
    delay(2000);

    //Check Light Sensor (if active)

    //Interpret Code
    switch (code)
    {
    case CODE_TYPE::VALID_CODE:
      scannerController->animationValidated();
      Serial.println("Success!");
      break;
    case CODE_TYPE::INVALID_CODE:
      scannerController->animationInvalidated();
      Serial.println("Failure!");
      break;
    case CODE_TYPE::TURN_OFF_SENSOR:
      scannerController->disableLightSensor();
      scannerController->animationSensorOff();
      Serial.println("Light Sensor Turned Off");
      break;
    case CODE_TYPE::XMAS_TIME:
      scannerController->animationXmas();
      soundController->playSong(SoundController::Song::Jinglebells);
      Serial.println("Merry Christmas!!");
      break;
    case CODE_TYPE::ORDER_66:
      scannerController->animationOrder66();
      soundController->playSong(SoundController::Song::Imperial);
      Serial.println("Death to the Jedi!");
      break;
    
    default:
      //failure animation
      Serial.println("Failure!");
      break;
    }

    //reset controllers
    keypadController->resetController();
    scannerController->resetController();
  }
  
}