#include "Scene.h"
#include "Globals.h" 

Scene* Scene::loop() {
  return NULL;
}

void Scene::activate() { 
  nudge();
}

void Scene::deactivate() { 
  
}

void Scene::nudge() { 
  _lastNudge = millis();
}

Scene *Scene::defaultTransition() { 
  if (millis() - _lastNudge > 30000) { 
    return &sleepScene;
  }
  return NULL;
}

