#include <SPI.h>
#include <TimerOne.h>

#include "Globals.h"
#include "GameField.h"
#include "LedMatrixDisplay.h"
#include "CubeDisplay.h"
#include "Keypad.h"
#include "SleepManager.h"

// Diagnostics
//#define ShowScreenAlignment 

// Game field size
#define Layers 6
#define Rows 6
#define Columns 6
// LED matrix arrangement
#define LedRows 6
#define LedColumns 36 // eventually 36
// Daisy chained shift registers driving LED matrix 
#define LedRowRegisters 1
#define LedColumnRegisters 5 // eventually 5 (enough for 36 bits) 
// Keypad
#define KeypadParallelLoadPin 6
#define KeypadClockEnablePin 7
#define KeypadDataPin 4
#define KeypadClockPin 5

// Globals
LedMatrixDisplay display(LedRows, LedColumns, LedRowRegisters, LedColumnRegisters); // 6x12 leds, 1x2 8-bit shift registers; data, latch, clock on 6, 7, 8
CubeDisplay cube(&display, Layers, Rows, Columns);
Keypad keypad(KeypadParallelLoadPin, KeypadClockEnablePin, KeypadDataPin, KeypadClockPin);
SleepManager sleep;
DemoScene demoScene;
MenuScene menuScene;
GameScene gameScene;
SleepScene sleepScene;
// End globals

Scene *currentScene = &menuScene;

#ifdef ShowScreenAlignment 
  currentScene = new ScreenAlignmentScene();
#endif

void mainTimer() {
  display.renderLoop();
}

void setup() {
  // Use 100 for 10kHz. At 10kHz display freq = 10kHz / 6 row / 21 phases = 80Hz
  Timer1.initialize(100);
  Timer1.attachInterrupt(mainTimer);
  display.clear();

  currentScene->activate();
}

void loop() {
  Scene *transition = currentScene->loop();
  if (transition != NULL) {
    currentScene->deactivate();
    currentScene = transition;
    display.clear();
    display.render();
    currentScene->activate();
  }
}
