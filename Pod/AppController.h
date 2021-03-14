#pragma once
#ifdef _AppController

#endif _AppController


#include<d3dx9math.h>
#include<string>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include"dxgraphics.h"
#include"ViewController.h"


// Read keyboard command
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)

class AppController {
	// Name of program
private:
	ViewController* rootViewController;

public:
	// Init
	AppController(ViewController* viewController);

	// Getter
	ViewController* getRootViewController();

	// Setter
	void setRootViewController(ViewController* _rootViewController);

	// Prototypes function
	int Game_Init(HWND);
	void Game_Run(HWND);
	void Game_End(HWND);
};