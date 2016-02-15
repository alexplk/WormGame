#include <SPI.h>
#include <TimerOne.h>

#include "GameField.h"
#include "LedMatrixDisplay.h"
#include "LedMatrixRenderer.h"
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
//// Segment display
//#define SegmentDisplayClock 3
//#define SegmentDisplayData 9
//#define SegmentDisplayLatch 8


LedMatrixDisplay disp(LedRows, LedColumns, LedRowRegisters, LedColumnRegisters);//, 4, 5, 6); // 6x12 leds, 1x2 8-bit shift registers; data, latch, clock on 6, 7, 8
LedMatrixRenderer renderer(&disp, Layers, Rows, Columns);

GameField field(Layers, Rows, Columns);
Keypad keypad(KeypadParallelLoadPin, KeypadClockEnablePin, KeypadDataPin, KeypadClockPin);
SleepManager sleep;

// SegmentDisplay segmentDisplay(SegmentDisplayData, SegmentDisplayLatch, SegmentDisplayClock);

#define AnimationLength 80
Direction _animation[AnimationLength] = { 
  {0, 1, 0},
  {0, 1, 0},
  {0, 1, 0},
  {0, 1, 0},
  {0, 1, 0},
  {0, 0, -1},
  {0, 0, -1},
  {0, 0, -1},
  {0, 0, -1},
  {0, 0, -1},
  {0, -1, 0},
  {0, -1, 0},
  {0, -1, 0},
  {0, -1, 0},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 0},
  {0, 1, 0},
  {0, 0, -1},
  {0, 0, -1},
  {0, 0, -1},
  {0, -1, 0},
  {0, -1, 0},
  {0, -1, 0},
  {0, 0, 1},
  {1, 0, 0},
  {0, 0, 1},
  {0, 0, 1},

  {1, 0, 0},

  {0, 1, 0},
  {0, 1, 0},
  {0, 1, 0},
  {0, 0, -1},
  {0, 0, -1},
  {0, 0, -1},
  {0, -1, 0},
  {0, -1, 0},

  {1, 0, 0},  {1, 0, 0},  {1, 0, 0},

  {0, 0, 1},
  {0, 0, 1},
  {0, 1, 0},
  {0, 0, -1}, 
  {0, 0, -1},
  {0, -1, 0},
  
  {0, -1, 0},
  {0, -1, 0},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 0},

  {-1, 0, 0},{-1, 0, 0},{-1, 0, 0},
  
  {0, 1, 0},  
  {0, 1, 0},  
  {0, 1, 0},
  {0, 0, -1},
  {0, 0, -1},
  
  {-1, 0, 0},

  {0, 0, -1},
  {0, 0, -1},
  {0, 0, -1},
  {0, -1, 0},
  {0, -1, 0},
  {0, -1, 0},
  {0, -1, 0},
  {0, -1, 0},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  
  {-1, 0, 0},
};


long tickCounter = 0;

void moveTimer() { 
  
}

void mainTimer() {
  if (tickCounter-- <= 0) {
    tickCounter = 10000;
    moveTimer();
  }
  disp.renderLoop();
}

void setup() {
  //Serial.begin(9600);

  // Use 100 for 10kHz. At 10kHz display freq = 10kHz / 6 row / 21 phases = 80Hz
  Timer1.initialize(100);
  Timer1.attachInterrupt(mainTimer);

  disp.clear();

  field.start({ 0,0,0 });
  for (byte i = 0; i < 5; i++)
    field.grow(DirectionRight);
  field.render(&renderer);
}

bool paused = false;
void loop() {

#ifdef ShowScreenAlignment
  renderer.renderScreenAlignment(&keypad);
  delay(100);
  return;
#endif

  for (int i = 0; i < AnimationLength; i++) {
  
    keypad.readShiftRegisters();
    while (keypad.isPressed(RightKey)) {
      keypad.readShiftRegisters();
      delay(200);
    }
    
    field.move(_animation[i]);
    field.render(&renderer);
    delay(300);
    
    //segmentDisplay.writeNumber((int)tickCounter);
  }
    
  sleep.sleepNow();
  
//  if (keypad.isPressed(RightKey)) {
//    paused = !paused;
//  }
//  if (keypad.isPressed(FrontKey)) {
//    field.move(DirectionForward);
//  }
//  if (keypad.isPressed(BackKey)) {
//    field.move(DirectionBackward);
//  }
//  if (keypad.isPressed(LeftKey)) {
//    field.move(DirectionLeft);
//  }
//  if (keypad.isPressed(RightKey)) {
//    field.move(DirectionRight);
//  }
//  if (keypad.isPressed(TopKey)) {
//    field.move(DirectionUp);
//  }
//  if (keypad.isPressed(BottomKey)) {
//    field.move(DirectionDown);
//  }

  
//  for (int i = 0; i < 8; i++) {
//    if ((keyBits & (1 << i)) != 0) {
//      disp->set(0, i, ON);
//      disp->set(i, 0, ON);
//    }
//  }
 
  //disp.renderLoop();
  //delay(1);
  //delayMicroseconds(10);
  
}
