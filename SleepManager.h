#pragma once 

#include <arduino.h>


class SleepManager { 
  
public:

  SleepManager();
  void sleep();
  void extend
  
private: 
  void init(byte groundPin, byte vccPin, byte dataPin, byte latchPin, byte clockPin);
  
}

