#pragma once

#include "LedMatrixDisplay.h"
//#include "IRenderer.h"

class CubeDisplay { // : public IRenderer { 
private: 
  LedMatrixDisplay *_display;
  byte _layers;
  byte _rows;
  byte _columns;
  
public: 
  CubeDisplay(LedMatrixDisplay *display, byte layers, byte rows, byte columns);

  byte layers();
  byte rows();
  byte columns();
  
  void clear();
  void render();
  void set(Cell cell, bool fill, byte sidesMask = 0b00111111);
  void set(byte l, byte r, byte c, bool fill, byte sidesMask = 0b00111111);

  void renderScreenAlignment(Keypad *keypad);
  bool isInBounds(Cell c);
  
private:
  CellProjection projectToSide(Cell cell, byte side);
  
};
