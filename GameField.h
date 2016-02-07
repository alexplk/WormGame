#pragma once 

#include <arduino.h>

#include "LedMatrixDisplay.h"
#include "Cell.h"
#include "IRenderer.h"

#define MaxWormLength 100

// 3D game field
class GameField {

private:
  byte _layers;
  byte _rows;
  byte _columns;
  //byte*** _cells;

  byte _wormLength;
  Cell _worm[MaxWormLength];

public:
  GameField(byte layers, byte rows, byte columns);

  void start(Cell c);
  bool grow(Direction d);
  bool move(Direction d);
  
  void render(IRenderer *display);

private: 

  

};

