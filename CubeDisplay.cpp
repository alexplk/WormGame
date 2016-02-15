#include "CubeDisplay.h"

byte depthToBrightness(byte d) {
  return max(OFF, ON - d); // d == 0 -> full brightness 
}

CubeDisplay::CubeDisplay(LedMatrixDisplay *display, byte layers, byte rows, byte columns) {
  _display = display;
  _layers = layers;
  _rows = rows;
  _columns = columns;
}

byte CubeDisplay::layers() {
  return _layers;
}

byte CubeDisplay::rows() {
  return _rows;
}

byte CubeDisplay::columns() {
  return _columns;
}

void CubeDisplay::clear() {
  _display->clear(); 
}

void CubeDisplay::render() {
  _display->render();
}

void CubeDisplay::set(byte l, byte r, byte c, bool fill, byte sidesMask) {
  Cell cell;
  cell.l = l;
  cell.r = r;
  cell.c = c;
  set(cell, fill, sidesMask);
}

void CubeDisplay::set(Cell cell, bool fill, byte sidesMask) {
  // Current implementation can only fill cells after full clear().
  // fill == false will be ignored. 

  if (!isInBounds(cell))
      return;
  
  if (!fill)
    return;
      
  for (byte s = 0; s < 6; s++) {
    if (((sidesMask >> s) & 1) != 0) {
      CellProjection p = projectToSide(cell, s);
      byte b = depthToBrightness(p.depth);
      byte prev = _display->get(p.row, p.column);
      if (b > prev)
        _display->set(p.row, p.column, b);
    }
  }
}

bool CubeDisplay::isInBounds(Cell c) {
  return 
    c.l >= 0 && c.l < _layers &&
    c.r >= 0 && c.r < _rows && 
    c.c >= 0 && c.c < _columns;
}

CellProjection CubeDisplay::projectToSide(Cell cell, byte side) {
  // See 'Display Sides.png'
  CellProjection p;
  p.depth = 100;
  switch (side) {
    case 0: 
      p.row = cell.r;
      p.column = cell.c;
      p.depth = cell.l;
      break;
    case 1: 
      p.row = cell.r;
      p.column = cell.l 
        + _columns; // screen offset
      p.depth = _columns - cell.c - 1;
      break;
    case 2:
      p.row = cell.r;
      p.column = _columns - cell.c - 1 
        + _columns + _layers; // screen offset
      p.depth = _layers - cell.l - 1;
      break;
    case 3: 
      p.row = cell.r;
      p.column = _layers - cell.l - 1 
        + _columns + _layers + _columns; // screen offset
      p.depth = cell.c;
      break;
    case 4: 
      p.row = _columns - cell.c - 1;
      p.column = _layers - cell.l - 1 
        + _columns + _columns + _layers + _layers; // screen offset
      p.depth = cell.r;
      break;
    case 5: 
      p.row = cell.c;
      p.column = _layers - cell.l - 1 
        + _columns + _columns + _layers + _layers + _layers; // screen offset
      p.depth = _rows - cell.r - 1;
      break;
  }

  return p;
}

void CubeDisplay::renderScreenAlignment(Keypad *keypad) {
  keypad->read();
  _display->clear();
  for (int s = 0; s < 6; s++) {
    for (int i = 0; i <= s; i++) _display->set(0, i + s * 6, ON);
    if (keypad->isPressed(1 << s)) {
      _display->set(2, s * 6 + 2, ON);
      _display->set(2, s * 6 + 3, ON);
      _display->set(3, s * 6 + 2, ON);
      _display->set(3, s * 6 + 3, ON);
    }
  }

  //  if (keypad.isPressed(FrontKey)) {
//    field.move(DirectionForward);
//  }
//  if (keypad.isPressed(BackKey)) {
//    field.move(DirectionBackward);
//  }
//  if (keypad.isPressed(LeftKey)) {
//    field.move(DirectionLeft);
//  }
//  if (keypad.isPressed(RightKey)) {
//    field.move(DirectionRight);
//  }
//  if (keypad.isPressed(TopKey)) {
//    field.move(DirectionUp);
//  }
//  if (keypad.isPressed(BottomKey)) {
//    field.move(DirectionDown);
//  }
  _display->render();
}

