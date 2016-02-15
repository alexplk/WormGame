#include "LedMatrixRenderer.h"

byte depthToBrightness(byte d) {
  return max(OFF, ON - d); // d == 0 -> full brightness 
}

LedMatrixRenderer::LedMatrixRenderer(LedMatrixDisplay *display, byte layers, byte rows, byte columns) {
  _display = display;
  _layers = layers;
  _rows = rows;
  _columns = columns;
}


void LedMatrixRenderer::clear() {
  _display->clear(); 
}

void LedMatrixRenderer::render() {
  _display->render();
}

void LedMatrixRenderer::set(Cell cell, bool fill) {
  // Current implementation can only fill cells after full clear().
  // fill == false will be ignored. 
  
  //_display->set(cell.r, cell.c, fill ? ON : OFF);
  
  if (!fill)
    return;
      
  for (byte s = 0; s < 6; s++) {
    CellProjection p = projectToSide(cell, s);
    byte b = depthToBrightness(p.depth);
    byte prev = _display->get(p.row, p.column);
    if (b > prev)
      _display->set(p.row, p.column, b);
  }
}

CellProjection LedMatrixRenderer::projectToSide(Cell cell, byte side) {
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

void LedMatrixRenderer::renderScreenAlignment(Keypad *keypad) {
  keypad->readShiftRegisters();
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

