#include "GameField.h"

GameField::GameField() {
  setSpeed(0);
}

GameField::GameField(byte layers, byte rows, byte columns) {
  setSize(layers, rows, columns);
  setSpeed(0);
}

void GameField::setSize(byte layers, byte rows, byte columns) {
  _layers = layers;
  _rows = rows;
  _columns = columns;
}

void GameField::setSpeed(byte speed) {
  _speed = speed;
  calculateInterval();
}

byte GameField::speed() {
  return _speed;
}

byte GameField::length() {
  return _wormLength;
}

void GameField::increaseSpeed() {
  _speed++;
  calculateInterval();
}

void GameField::calculateInterval() {
  int freq = 60 + _speed * 30; // per minute
  _moveInterval = 60000 / freq;
}

long GameField::millisToMove() {
  return _moveResetMillis + _moveInterval - millis();
}

void GameField::resetMoveTimer() {
  _moveResetMillis = millis();
}

void GameField::start(Cell c) {
  _wormLength = 1;
  _worm[0] = c;
  stopExplosion();
}

bool GameField::grow(Direction d) {
  _lastDirection = d;
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
  resetMoveTimer();
  return true;
}

bool GameField::move(Direction d) {
  _lastDirection = d;
  if (grow(d)) {
    _wormLength--;
  }
}

int GameField::getSegmentIndex(Cell c) {
  for (byte i = 0; i < _wormLength; i++)
    if (c == _worm[i]) 
      return i;
  return -1;
}

bool GameField::isInBounds(Cell c) {
  return 
    c.l >= 0 && c.l < _layers &&
    c.r >= 0 && c.r < _rows && 
    c.c >= 0 && c.c < _columns;
}

Cell GameField::getHeadCell() { 
  return _worm[0];
}

Direction GameField::lastDirection() {
  return _lastDirection;
}

void setCoord(CubeDisplay *cube, byte l, byte r, byte c) {
  Cell cell;
  cell.l = l;
  cell.r = r;
  cell.c = c;
  cube->set(cell, true);
}

void GameField::render(CubeDisplay *cube, byte sidesMask, bool clear) {
  if (clear) 
    cube->clear();

  // Render the worm
  for (byte i = 0; i < _wormLength; i++) {
    Cell c = _worm[i];
    cube->set(c, isSegmentVisible(i), sidesMask);
  }

  // Render wall explosion 
  if (_isExplodingWall) { 
    renderWallExplosion(cube);
  }
  
  cube->render();
}

void GameField::explodeHead() {
  _explosionTime = millis();
  _isExplodingHead = true;
}

void GameField::explodeWall(Direction dir) {
  _explosionTime = millis();
  
  for (byte s = 0; s < 6; s++) {
    if (dir == Directions[s]) {
      _isExplodingWall = true;
      _wallExplosionSide = 1 << s;
      _wallExplosionDirection = dir;
      break;
    }
  }
}

void GameField::explodeBody(byte segmentIndex) {
  _explosionTime = millis();
  _isExplodingBody = true;
  _bodyExplosionStartSegment = segmentIndex;
}

void GameField::stopExplosion() {
  _isExplodingHead = false;
  _isExplodingWall = false;
  _isExplodingBody = false;
}

bool GameField::isSegmentVisible(byte index) {
  if (_isExplodingHead) {
    if (index == 0) {
      long elapsed = millis() - _explosionTime;
      // Second highest bit determines whether light is on or off. 
      // Blink fast close to explosion. 
      byte highBit = 0;
      for (byte b = 0; b < 32; b++) {
        if ((elapsed >> b) != 0)
          highBit = b;
      }
      // Stop increasing frequency at 2^9 (512ms).
      highBit = min(highBit, 9);
      return ((elapsed >> (highBit - 2)) & 1) == 1;
    }
  }
  if (_isExplodingBody) {
    long elapsed = millis() - _explosionTime;
    int frame = elapsed >> 7;
    if (index == _bodyExplosionStartSegment - frame || 
        index == _bodyExplosionStartSegment + frame) 
    {
      return false;
    }
  }
  return true;
}

void GameField::renderWallExplosion(CubeDisplay *cube) {
  if (!_isExplodingWall)
    return;
  Cell point = _worm[0];
  long elapsed = millis() - _explosionTime;
  int frame = elapsed >> 6;
  byte side = 0xFF; // _wallExplosionSide; 
  Direction dx, dy; 
  if (_wallExplosionDirection.l != 0) {
    dx = { 0, 1, 0 };
    dy = { 0, 0, 1 }; 
  }
  if (_wallExplosionDirection.r != 0) {
    dx = { 1, 0, 0 };
    dy = { 0, 0, 1 }; 
  }
  if (_wallExplosionDirection.c != 0) {
    dx = { 1, 0, 0 };
    dy = { 0, 1, 0 }; 
  }
  switch (frame) { 
    case 0: 
      cube->set(point + dx, true, side);
      cube->set(point + dy, true, side);
      cube->set(point - dx, true, side);
      cube->set(point - dy, true, side);
      break;
    case 1: 
      cube->set(point - dy*2 - dx, true, side);
      cube->set(point - dy*2, true, side);
      cube->set(point - dy*2 + dx, true, side);
      cube->set(point - dx*2 - dy, true, side);
      cube->set(point - dx*2, true, side);
      cube->set(point - dx*2 + dy, true, side);
      cube->set(point + dy*2 - dx, true, side);
      cube->set(point + dy*2, true, side);
      cube->set(point + dy*2 + dx, true, side);
      cube->set(point + dx*2 - dy, true, side);
      cube->set(point + dx*2, true, side);
      cube->set(point + dx*2 + dy, true, side);
      break;
    case 2: 
      cube->set(point - dy*3 - dx, true, side);
      cube->set(point - dy*3, true, side);
      cube->set(point - dy*3 + dx, true, side);
      cube->set(point - dy*2 + dx*2, true, side);
      cube->set(point - dx*3 + dy, true, side);
      cube->set(point - dx*3, true, side);
      cube->set(point - dx*3 - dy, true, side);
      cube->set(point - dx*2 - dy*2, true, side);
      cube->set(point + dy*3 - dx, true, side);
      cube->set(point + dy*3, true, side);
      cube->set(point + dy*3 + dx, true, side);
      cube->set(point + dy*2 - dx*2, true, side);
      cube->set(point + dx*3 - dy, true, side);
      cube->set(point + dx*3, true, side);
      cube->set(point + dx*3 + dy, true, side);
      cube->set(point + dx*2 + dy*2, true, side);
      break;
  }
}
