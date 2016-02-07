#pragma once 

#include <arduino.h>

class SegmentDisplay {
  byte _groundPin; 
  byte _vccPin; 
  byte _dataPin;
  byte _latchPin;
  byte _clockPin;

public:
  SegmentDisplay(byte dataPin, byte latchPin, byte clockPin);
  SegmentDisplay(byte groundPin, byte vccPin, byte dataPin, byte latchPin, byte clockPin);
  SegmentDisplay(byte firstPinGround);
  void writeNumber(int number);

private: 
  void init(byte groundPin, byte vccPin, byte dataPin, byte latchPin, byte clockPin); 
};
