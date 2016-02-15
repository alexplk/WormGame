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
  
}

void GameScene::deactivate() { 
  
}

void GameScene::startGame(GameField *field) {
  _field = field;
  _nextDirection = _field->lastDirection();
}

Scene* GameScene::loop() {

  while (true) {
    byte key = keypad.read();
    Direction d = keyToDirection(key);
    if (d != DirectionNone && 
        // ignore move back
        1 != _field->getSegmentIndex(_field->getHeadCell() + d)) { 
      _nextDirection = d;
    }
    
    if (_field->millisToMove() <= 0) {
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
        _field->move(_nextDirection);
      } else { // end game animation
        _field->explodeHead();
        while (_field->millisToMove() > -15000) {
          _field->render(&cube);
          delay(10);
          if (_field->millisToMove() < -1000) {
            if (keypad.read()) {
              return &menuScene;
            }
          }
        }
        return &sleepScene;
      }
    }
  
    _field->render(&cube);
  
    delay(10);
  }
  return NULL;
}

