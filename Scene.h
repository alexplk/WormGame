#pragma once

#include <arduino.h>

#include "LedMatrixDisplay.h"
#include "Keypad.h"
#include "SleepManager.h"

class Scene { 
private:
  long _lastNudge;
protected: 
  void nudge(); // reset sleep timer
  Scene *defaultTransition();
public: 
  virtual Scene* loop(); // Returns scene if transition needed
  virtual void activate();
  virtual void deactivate();
  
};

