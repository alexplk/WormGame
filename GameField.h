#pragma once 

#include <arduino.h>

#include "LedMatrixDisplay.h"
#include "Cell.h"
#include "CubeDisplay.h"

#define MaxWormLength 10

// 3D game field
class GameField {

private:
  byte _layers;
  byte _rows;
  byte _columns;
  byte _speed;
  long _moveInterval;
  long _moveResetMillis;
  Direction _lastDirection;
  byte _wormLength;
  Cell _worm[MaxWormLength];
  long _explosionTime;
  bool _isExplodingHead;
  bool _isExplodingWall;
  bool _isExplodingBody;
  bool _isGrowingBody;
  byte _wallExplosionSide;
  Direction _wallExplosionDirection;
  byte _bodyExplosionStartSegment;
  byte _seedCount; 
  Cell _seed;
  
public:
  GameField();
  GameField(byte layers, byte rows, byte columns);
  void setSize(byte layers, byte rows, byte columns);
  void setSpeed(byte speed); 
  byte speed();
  byte length();
  void increaseSpeed();
  long millisToMove();
  void resetMoveTimer();
  void start(Cell c);
  bool grow(Direction d);
  bool move(Direction d);
  int getSegmentIndex(Cell c);
  bool isInBounds(Cell c);
  void render(CubeDisplay *cube, byte sidesMask = 0b00111111, bool clear = true);
  Direction lastDirection();
  void explodeHead();
  void explodeWall(Direction dir);
  void explodeBody(byte segmentIndex);
  void growBody();
  Cell getHeadCell();
  byte seedCount(); 
  Cell createRandomSeed();
  void removeSeed();
  bool isSeed(Cell c); 
  
private: 

  void calculateInterval();
  bool isSegmentVisible(byte index);
  void stopExplosion();
  void renderWallExplosion(CubeDisplay *cube);
  void renderSeeds(CubeDisplay *cube);
};

