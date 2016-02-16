#include "GameScene.h"
#include "Globals.h"

Direction keyToDirection(byte key) { 
  switch (key) {
    case FrontKey: 
      return DirectionBackward; // toward front
    case BackKey: 
      return DirectionForward; // toward back
    case LeftKey:
      return DirectionLeft;
    case RightKey:
      return DirectionRight;
    case TopKey: 
      return DirectionUp;
    case BottomKey:
      return DirectionDown;
    default:
      return DirectionNone;   
  }
}

GameScene::GameScene() {
  
}

void GameScene::activate() {
  _collectedTotal = 0;
  _collectedSinceSpeedUp = 0;
}

void GameScene::deactivate() { 
  
}

void GameScene::startGame(GameField *field) {
  _field = field;
  _nextDirection = _field->lastDirection();
}

Scene* GameScene::loop() {
  byte key = keypad.read();
  Direction d = keyToDirection(key);
  if (d != DirectionNone && 
      // ignore move back
      1 != _field->getSegmentIndex(_field->getHeadCell() + d)) { 
    _nextDirection = d;
  }
  
  if (_field->millisToMove() <= 0) {
    nudge();
    bool exploded = false;
    Cell moveTo = _field->getHeadCell() + _nextDirection;
    int seg = _field->getSegmentIndex(moveTo); 
    if (seg != -1 && seg != _field->length() - 1) { // can move to the tail's place - it will move out
      _field->explodeBody(seg);
      exploded = true;
    }
    if (!_field->isInBounds(moveTo)) { 
      _field->explodeWall(_nextDirection);
      exploded = true;
    }
    if (!exploded) { 
      if (_field->isSeed(moveTo)) {
        _field->grow(_nextDirection);
        _field->growBody();
        _field->removeSeed();
        _collectedTotal++;
        _collectedSinceSpeedUp++;
        if (_collectedSinceSpeedUp == 10) {
          _field->increaseSpeed();
          _collectedSinceSpeedUp = 0;
        }
      } else {
        _field->move(_nextDirection);
        if (_field->seedCount() == 0) {
          _field->createRandomSeed();
        }
      }
    } else { // end game animation
      _field->explodeHead();
      _field->removeSeed();
      Scene *t = defaultTransition();
      while (t == NULL) {
        _field->render(&cube);
        delay(10);
        if (_field->millisToMove() < -1000) {
          if (keypad.read()) {
            return &menuScene;
          }
        }
        t = defaultTransition();
      }
      return t;
    }
  }

  _field->render(&cube);

  delay(10);
  return defaultTransition();
}

