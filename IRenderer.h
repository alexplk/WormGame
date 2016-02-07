#pragma once 

#include "Cell.h"


// Adapter between 3D game field and a specific display.
class IRenderer { 
public:
  virtual ~IRenderer() {}
  virtual void clear() = 0;
  virtual void set(Cell cell, bool fill) = 0;
  virtual void render() = 0;
};

