#pragma once
#ifdef _AppController

#endif _AppController


#include <d3dx9math.h>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "dxgraphics.h"
#include "WorldVC.h"
#include "SunnyVC.h"
#include "UndergroundVC.h"


// Read keyboard command
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)

class AppController {
	// Name of program
private:
	//ViewController* rootViewController;
	SceneName sceneName = WorldScene;

	WorldVC* worldVC;
	SunnyVC* sunnyVC;
	UndergroundVC* undergroundVC;



public:

	// Getter
	//ViewController* getRootViewController();
	SceneName getSceneName();
	WorldVC* getWorldVC();
	SunnyVC* getSunnyVC();
	UndergroundVC* getUndergroundVC();




	// Setter
	//void setRootViewController(SceneName _sceneName);
	void setSceneName(SceneName _sceneName);
	void setWorldVC(WorldVC* _worldVC);
	void setSunnyVC(SunnyVC* _sunnyVC);
	void setUndergroundVC(UndergroundVC* _undergroundVC);




	// Prototypes function
	int Game_Init(HWND hwnd);
	void Game_Run(HWND hwnd, float _dt);
	void Game_End(HWND hwnd);
	void Handler_Keyboard(HWND hwnd);
};