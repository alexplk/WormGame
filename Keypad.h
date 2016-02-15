#pragma once 

#include <arduino.h>

#define FrontKey  0b00000001
#define RightKey  0b00000010
#define BackKey   0b00000100
#define LeftKey   0b00001000
#define TopKey    0b00010000
#define BottomKey 0b00100000

#define KeyCount 6

// http://playground.arduino.cc/Code/ShiftRegSN74HC165N
// Serial-in shift register SN74HC165N 

class Keypad { 
private: 
  byte _ploadPin;
  byte _clockEnablePin;
  byte _dataPin;
  byte _clockPin;
  byte _lastState;
  bool _handled;
public: 
  // Function - SN74HC165N pin
  // pload    - pin 1   SH/LD
  // clockEn  - pin 15  CLK INH
  // data     - pin 9   QH
  // clock    - pin 2   CLK
  Keypad(byte ploadPin, byte clockEnablePin, byte dataPin, byte clockPin);
  bool isPressed(byte key);
  bool readKey(byte key);
  byte read();
  void handled();
//private: 
  
};

