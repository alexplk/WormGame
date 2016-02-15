#pragma once 

#include "Scene.h"

class SleepScene : public Scene {
private: 
public: 
  SleepScene();
  Scene *loop();
  void activate();
};

