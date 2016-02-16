#include "MenuScene.h"
#include "Globals.h"

MenuScene::MenuScene() {
  
}

void MenuScene::activate() { 
  Scene::activate();
  
  for (int s = 0; s < 6; s++) {
    _gameFields[s].setSize(cube.layers(), cube.rows(), cube.columns());
  }
  // complexity levels 
  // Level 0. Side 0
  _gameFields[0].setSpeed(0);
  _gameFields[0].start({ 0, 0, 0 });
  _gameFields[0].grow(DirectionRight);
  // Level 1. Side 3
  _gameFields[3].setSpeed(1);
  _gameFields[3].start({ 0, 0, 0 });
  _gameFields[3].grow(DirectionDown);
  _gameFields[3].grow(DirectionDown);
  // Level 2. Side 4
  _gameFields[4].setSpeed(2);
  _gameFields[4].start({ 0, 0, 0 });
  _gameFields[4].grow(DirectionForward);
  _gameFields[4].grow(DirectionForward);
  _gameFields[4].grow(DirectionForward);
  // Level 3. Side 2
  _gameFields[2].setSpeed(3);
  _gameFields[2].start({ 5, 5, 5 });
  _gameFields[2].grow(DirectionLeft);
  _gameFields[2].grow(DirectionLeft);
  _gameFields[2].grow(DirectionLeft);
  _gameFields[2].grow(DirectionUp);
  // Level 4. Side 1
  _gameFields[1].setSpeed(4);
  _gameFields[1].start({ 5, 5, 5 });
  _gameFields[1].grow(DirectionUp);
  _gameFields[1].grow(DirectionUp);
  _gameFields[1].grow(DirectionUp);
  _gameFields[1].grow(DirectionBackward);
  _gameFields[1].grow(DirectionBackward);
  // Level 5. Side 5
  _gameFields[5].setSpeed(5);
  _gameFields[5].start({ 5, 5, 5 });
  _gameFields[5].grow(DirectionBackward);
  _gameFields[5].grow(DirectionBackward);
  _gameFields[5].grow(DirectionBackward);
  _gameFields[5].grow(DirectionLeft);
  _gameFields[5].grow(DirectionLeft);
  _gameFields[5].grow(DirectionLeft);
  
  for (int s = 0; s < 6; s++) {
    _gameFields[s].render(&cube, 1 << s, false);
  }

  //cube.set({ 2, 3, 4 }, true);
  cube.render();
  delay(500);
}

void MenuScene::deactivate() {
  
}

Scene *MenuScene::loop() {
  byte key = keypad.read();
  if (key != 0) { 
    keypad.handled();

    byte side = -1;
    for (byte s = 0; s < 6; s++) {
      if (key == (1 << s)) {
        side = s;
        break;
      }
    }
    if (side != -1) {
      for (byte i = 0; i < 3; i++) {
        _gameFields[side].render(&cube, 1 << side);
        cube.render();
        delay(100);
        cube.clear();
        cube.render();
        delay(100);
      }
      for (byte i = 0; i < 3; i++) {
        _gameFields[side].render(&cube);
        cube.render();
        delay(200);
        cube.clear();
        cube.render();
        delay(200);
      }

      gameScene.startGame(&_gameFields[side]);
      return &gameScene;
    }
  }
  delay(10);
  return Scene::defaultTransition();
}


