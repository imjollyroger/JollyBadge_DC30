/*

  JollyBadge_DC30
  By: JollyRoger

*/

#include <Adafruit_NeoPixel.h>
#include <FlashAsEEPROM.h>
#include <FlashStorage.h>
#include <Wire.h>
#include <ST25DVSensor.h>
#include <ArduinoLowPower.h>
#include <MPU6050_light.h>

// MCU CLOCK DIVIDER
int CLOCK_DIVIDER = 12;
// int CLOCK_DIVIDER = 1;
enum MCUState {
  fast,
  slow
};

// GAME STATE
enum GameState {
  initializing,
  pNFC,
  pMorseCode,
  pBinary,
  pSerial,
  pDataDump,
  pCrypto,
  complete,
  finalBling
};

// NEO-PIXELS
#define PIXEL_PIN         0
#define PIXEL_OFFSET      3
#define PIXEL_BRIGHTNESS  20
#define PIXEL_NUM         8
Adafruit_NeoPixel         pixels(PIXEL_NUM, PIXEL_PIN);

enum AnimationState {
  none,
  pulse,
  success,
  failure,
  aComplete,
  bling
};
bool currentlyAnimating   = false;

// NFC
#define GPO_PIN 199 // Assignment doesn't matter, just don't conflict
#define LPD_PIN 198 // Assignment doesn't matter, just don't conflict
#define SDA_PIN 4
#define SCL_PIN 5
#define WireNFC Wire
String currentText  = "";
String currentHint  = "";

// IMU
MPU6050 mpu(Wire);
float x, y, z     = 0.0;
float currTemp    = 0.0;
float targetTemp  = 0.0;
float currAngle   = 0.0;
float targetAngle = 0.0;

// DECLARATIONS
void switchMCUState(MCUState state);
void setTemporaryGameState(GameState nextState);
void setGameState(GameState nextState);
void setCurrentAnimationState(AnimationState state);

//OTHER
bool didWriteHint = false;
bool pauseChecks = false;
bool pauseState = false;
