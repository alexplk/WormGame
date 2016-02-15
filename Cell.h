#pragma once 

#include <arduino.h>

typedef struct Direction { 
  byte l, r, c;
  
  Direction operator+(const Direction& d) const
  {
    return { l + d.l, r + d.r, c + d.c };
  }
  
  bool operator==(const Direction& d) const
  {
    return (l == d.l && r == d.r && c == d.c);
  }

};

//typedef struct Direction Direction;

typedef struct Cell { 
  byte l, r, c;

//  Cell(byte layer, byte row, byte column) {
//    l = layer;
//    r = row;
//    c = column;
//  }
//  
  Cell operator+(const Cell& d) const
  {
    return { l + d.l, r + d.r, c + d.c };
  }
  
  Cell operator+(const Direction& d) const
  {
    return { l + d.l, r + d.r, c + d.c };
  }
  
  bool operator==(const Cell& d) const
  {
    return (l == d.l && r == d.r && c == d.c);
  }
};

//typedef struct Cell Cell;

static const Direction DirectionRight = { 0, 0, 1 };
static const Direction DirectionLeft = { 0, 0, -1 };
static const Direction DirectionUp = { 0, -1, 0 };
static const Direction DirectionDown = { 0, 1, 0 };
static const Direction DirectionForward = { 1, 0, 0 };
static const Direction DirectionBackward = { -1, 0, 0 };

