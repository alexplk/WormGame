#pragma once

#include <arduino.h>

#include "LedMatrixDisplay.h"
#include "Keypad.h"
#include "SleepManager.h"

class Scene { 
private:
public: 
  virtual Scene* loop(); // Returns scene if transition needed
  virtual void activate();
  virtual void deactivate();
};

