#pragma once

#include "LedMatrixDisplay.h"
#include "IRenderer.h"

class LedMatrixRenderer : public IRenderer { 
private: 
  LedMatrixDisplay *_display;
  byte _layers;
  byte _rows;
  byte _columns;
  
public: 
  LedMatrixRenderer(LedMatrixDisplay *display, byte layers, byte rows, byte columns);
  
  void clear();
  void render();
  void set(Cell cell, bool fill);

private:
  CellProjection projectToSide(Cell cell, byte side);
  
};
