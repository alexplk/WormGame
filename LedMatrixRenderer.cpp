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
      p.column = cell.l + _columns;
      p.depth = _columns - cell.c - 1;
      break;
    case 2: // Version for 3 sides, 3rd on top
      p.row = cell.c;
      p.column = cell.l + _columns + _columns;
      p.depth = cell.r;
      break;
  }

  return p;
}
