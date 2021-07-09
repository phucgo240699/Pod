#pragma once
#ifdef _AppController

#endif _AppController


#include <d3dx9math.h>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "dxgraphics.h"
#include "SunnyVC.h"
#include "WorldVC.h"
#include "SceneName.h"


// Read keyboard command
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)

class AppController {
	// Name of program
private:
	ViewController* rootViewController;

	//WorldVC* worldVC;
	//SunnyVC* sunnyVC;
public:

	// Getter
	ViewController* getRootViewController();

	// Setter
	void setRootViewController(SceneName _sceneName);

	// Prototypes function
	int Game_Init(HWND hwnd);
	void Game_Run(HWND hwnd, float _dt);
	void Game_End(HWND hwnd);
	void Handler_Keyboard(HWND hwnd);
};