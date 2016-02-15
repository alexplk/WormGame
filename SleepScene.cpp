#include "SleepScene.h"
#include "Globals.h"

SleepScene::SleepScene() {
  
}

void SleepScene::activate() { 
  sleep.sleepNow();
}

Scene *SleepScene::loop() {
  bool keyPressed = false;
  while (!keyPressed) {
    for (int i = 0; i < 30; i++) {
      if (keypad.read()) { 
        keypad.handled();
        return &menuScene;
      }
      if (i == 0) {
        cube.clear();
        cube.set(0, 0, 0, true);
        cube.set(cube.layers() - 1, cube.rows() - 1, cube.columns() - 1, true);
        cube.render();
        delay(10);
      }
      cube.clear();
      cube.render();
      delay(100);
    }
  }
}

