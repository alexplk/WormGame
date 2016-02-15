#pragma once

#include "LedMatrixDisplay.h"
#include "CubeDisplay.h" 
#include "Keypad.h"
#include "SleepManager.h"

#include "Scene.h"
#include "DemoScene.h"
#include "SleepScene.h"
#include "MenuScene.h"
#include "GameScene.h"

extern LedMatrixDisplay display;
extern CubeDisplay cube;
extern Keypad keypad;
extern SleepManager sleep;
extern DemoScene demoScene;
extern MenuScene menuScene;
extern GameScene gameScene;
extern SleepScene sleepScene;
