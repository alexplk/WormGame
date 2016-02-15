#pragma once 

#include "Scene.h"
#include "GameField.h"

class DemoScene : public Scene {
private: 
  Direction *_animation;
  GameField *_field;
public: 
  DemoScene();
  Scene* loop();
};
