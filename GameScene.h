#pragma once 

#include "Scene.h"
#include "GameField.h"

class GameScene : public Scene {
private:
  GameField *_field;
  Direction _nextDirection;
  int _collectedTotal;
  int _collectedSinceSpeedUp;
  
public: 
  GameScene();
  Scene* loop();
  void activate();
  void deactivate();
  void startGame(GameField *field);
};

