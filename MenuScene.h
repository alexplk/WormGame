#pragma once 

#include "Scene.h"
#include "GameField.h"

class MenuScene : public Scene {
private: 
  GameField _gameFields[6];
public: 
  MenuScene();
  Scene *loop();
  void activate();
  void deactivate();
};

