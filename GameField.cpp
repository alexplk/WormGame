#include "GameField.h"

GameField::GameField(byte layers, byte rows, byte columns) {
  _layers = layers;
  _rows = rows;
  _columns = columns;
//  _cells = new byte**[_layers];
//  for (int l = 0; l < _layers; l++) {
//    _cells[l] = new byte*[_rows];
//    for (int r = 0; r < _rows; r++) {
//      _cells[l][r] = new byte[_columns];
//      for (int c = 0; c < _columns; c++) {
//        _cells[l][r][c] = 0;
//      }
//    }
//  }
//  byte a = _cells[0][1][2];
}

void GameField::start(Cell c) {
  _wormLength = 1;
  _worm[0] = c;
}

bool GameField::grow(Direction d) {
  if (_wormLength == MaxWormLength) {
    _wormLength--;
  }
  Cell c = _worm[0] + d;
  if (c.l < 0 || c.l >= _layers ||
      c.r < 0 || c.r >= _rows || 
      c.c < 0 || c.c >= _columns) 
      return false;
      
  for (byte i = _wormLength; i > 0; i--) {
    _worm[i] = _worm[i - 1];
  }
  _worm[0] = c;
  _wormLength++;

  return true;
}

bool GameField::move(Direction d) {
  if (grow(d)) {
    _wormLength--;
  }
}

void setCoord(IRenderer *disp, byte l, byte r, byte c) {
  Cell cell;
  cell.l = l;
  cell.r = r;
  cell.c = c;
  disp->set(cell, true);
}

void GameField::render(IRenderer *display) {
  display->clear();
  for (byte i = 0; i < _wormLength; i++) {
    Cell c = _worm[i];
    display->set(c, true);
  }
//
//  // temp
//  setCoord(display, 0, 0, 0);
//  setCoord(display, 0, 0, 5);
//  setCoord(display, 0, 5, 0);
//  setCoord(display, 0, 5, 5);
//  setCoord(display, 5, 0, 0);
//  setCoord(display, 5, 0, 5);
//  setCoord(display, 5, 5, 0);
//  setCoord(display, 5, 5, 5);  
//  
  display->render();
}

