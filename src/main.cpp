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
  //scannerController->lightSensorTest();
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
//- Light Sensor Calibration
//-  helper function to calibrate light sensor
//=========================================================
bool calibration = false;
int temp_background = 0;
int temp_hand = 0;
int temp = 0;
void runCalibrationMode(void)
{
  //enum CAL_STEPS {TAKE_BACKGROUND_READING, TAKE_HAND_READING, THRESHOLD_ADJUST};
  //CAL_STEPS step = CAL_STEPS::TAKE_BACKGROUND_READING;
  int key = -1;

  //Only process if keystroke detected
  if(keypadController->getKeyStroke(&key))
  {
    Serial.printf("Running Calibration... Key:%d\n", key);
    switch (key)
    {
    case 0:
      //Exit Mode
      calibration = false;
      temp_background = 0;
      temp_hand = 0;
      temp = 0;
      Serial.println("Leaving Calibration...");
      scannerController->animationCalibrationStep();
      soundController->playSoundFX(SoundController::SoundFX::Fireball);
      break;
    case 55:
      //Take Background
      temp_background = scannerController->takeSensorSample();
      Serial.printf("Running Calibration... Background:%d\n", temp_background);
      scannerController->animationCalibrationStep();
      soundController->playSoundFX(SoundController::SoundFX::Fireball);
      break;
    case 99:
      //Take Hand
      temp_hand = scannerController->takeSensorSample();
      Serial.printf("Running Calibration... Hand:%d\n", temp_hand);
      scannerController->animationCalibrationStep();
      soundController->playSoundFX(SoundController::SoundFX::Fireball);
      break;
    case 2:
      //Set Threshold
      scannerController->setSensorThreshold(temp_background - temp_hand - 5);
      Serial.printf("Running Calibration... Threshold:%d\n", temp_background - temp_hand);
      scannerController->animationCalibrationStep();
      soundController->playSoundFX(SoundController::SoundFX::Fireball);
      break;
    case 1:
      //Bump Threshold Up
      temp = scannerController->getSensorThreshold() + 10;
      scannerController->setSensorThreshold(temp);
      Serial.printf("Running Calibration... Increase Threshold:%d\n", temp);
      scannerController->animationCalibrationStep();
      soundController->playSoundFX(SoundController::SoundFX::Fireball);
      break;
    case 3:
      //Bump Threshold Down
      temp = scannerController->getSensorThreshold() - 10;
      temp = (temp < 10)?10:temp;
      scannerController->setSensorThreshold(temp);
      Serial.printf("Running Calibration... Decrease Threshold:%d\n", temp);
      scannerController->animationCalibrationStep();
      soundController->playSoundFX(SoundController::SoundFX::Fireball);
      break;
    
    default:
      //do nothing
      break;
    }
  }
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
  //system_test(); return;

  //Run Calibration
  if(calibration) {
    runCalibrationMode();
    return;
  }

  //Check for hand present
  if(scannerController->isHandPresent()) {
      //Serial.println("Sensor Reading: Hand on Scanner");
      scannerController->animationReady();
  }
  else {
      //Serial.println("Sensor Reading: Hand off Scanner");
      scannerController->clearDisplay();
  }

  //Register Keystroke
  CODE_TYPE code = keypadController->registerKeypress();

  //Check for Full Code
  if(code != CODE_TYPE::CODE_IMPCOMPLETE)
  {
    //Start Scanning Animation
    if((code != CODE_TYPE::TURN_OFF_SENSOR) && (code != CODE_TYPE::CALIBRATION))
    {
      scannerController->animationScanning();
      scannerController->clearDisplay();
      delay(200);
    }

    //Check Light Sensor (if active)
    //Make sure hand is still present
    scannerController->clearHandPresent();
    if(!scannerController->isHandPresent() &&
       ((code != CODE_TYPE::TURN_OFF_SENSOR) && (code != CODE_TYPE::CALIBRATION))) 
    {
      //overwrite code
      Serial.println("Failed second hand check");
      code = CODE_TYPE::INVALID_CODE;
    }

    //Interpret Code
    switch (code)
    {
    case CODE_TYPE::VALID_CODE:
      scannerController->animationValidated();
      soundController->playSoundFX(SoundController::SoundFX::OneUp);
      delay(1500);
      scannerController->clearDisplay();
      Serial.println("Success!");
      break;
    case CODE_TYPE::INVALID_CODE:
      scannerController->animationInvalidated();
      soundController->playSoundFX(SoundController::SoundFX::Failure);
      //soundController->playSong(SoundController::Song::Fail);
      delay(1500);
      scannerController->clearDisplay();
      Serial.println("Failure!");
      break;
    case CODE_TYPE::TURN_OFF_SENSOR:
      scannerController->toggleLightSensor();
      scannerController->animationSensorOff();
      soundController->playSoundFX(SoundController::SoundFX::Coin);
      scannerController->clearDisplay();
      Serial.println("Light Sensor Turned Off");
      break;
    case CODE_TYPE::CALIBRATION:
      calibration = true;
      scannerController->animationCalibration();
      soundController->playSoundFX(SoundController::SoundFX::Fireball);
      scannerController->clearDisplay();
      Serial.println("Enter Calibration Mode...");
      break;
    case CODE_TYPE::XMAS_TIME:
      scannerController->animationXmas();
      soundController->playSong(SoundController::Song::Jinglebells);
      scannerController->clearDisplay();
      Serial.println("Merry Christmas!!");
      break;
    case CODE_TYPE::ORDER_66:
      scannerController->animationOrder66();
      soundController->playSong(SoundController::Song::Imperial);
      scannerController->clearDisplay();
      Serial.println("Death to the Jedi!");
      break;
    case CODE_TYPE::CANNON:
      scannerController->animationCannon();
      soundController->playSong(SoundController::Song::Cannon);
      scannerController->clearDisplay();
      Serial.println("Cannon in D");
      break;
    case CODE_TYPE::MARIO:
      scannerController->animationMario();
      soundController->playSong(SoundController::Song::Mario);
      scannerController->clearDisplay();
      Serial.println("Lets go Mario!");
      break;
    case CODE_TYPE::LION:
      scannerController->animationLion();
      soundController->playSong(SoundController::Song::Lion);
      scannerController->clearDisplay();
      Serial.println("Ahhhh-weeeeee!");
      break;
    case CODE_TYPE::TETRIS:
      scannerController->animationTetris();
      soundController->playSong(SoundController::Song::Tetris);
      scannerController->clearDisplay();
      Serial.println("Beep, boop, badooop....");
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