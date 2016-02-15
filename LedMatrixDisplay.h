#pragma once 

#include <arduino.h>
#include <SPI.h> 
#include "Cell.h"
#include "Keypad.h"

#define ON 3
#define HALF 2
#define QUARTER 1
#define OFF 0

// Projection of a 3D cell to a side of the cube 
typedef struct CellProjection { 
  byte row, column;
  byte depth;
};

// 2D LED matrix display. Stores brightness of all LEDs. Controls multiplexing and PWM.
class LedMatrixDisplay { 
private: 
//  byte _dataPin;
//  byte _clockPin;
  byte _latchPin;
  byte _rows;
  byte _columns;
  byte _rowRegisters;
  byte _columnRegisters;
  byte **_cells; // [ Rows ] * [ Cells ]
  byte _renderRow; 
  byte _renderShadeLayer;
  int _renderShadeLayerTicksRemaining;

  byte ***_rawColumnBits; // [ Shades-1 ] * [ Rows ] * [ colRegs ] = 3 * 6 * 5 = 90
  byte **_rawRowBits; // [ Rows ] * [ rowRegs ] = 6 * 1 = 6
  
public:
  LedMatrixDisplay(byte rows, byte columns, byte rowRegisters, byte columnRegisters); //, byte dataPin, byte latchPin, byte clockPin);
  void set(byte row, byte column, byte value);
  byte get(byte row, byte column);
  void renderLoop();
  void clear();
  void render();

//  virtual void clear();
//  virtual void render();
//  virtual void set(Cell cell, bool fill);


};

