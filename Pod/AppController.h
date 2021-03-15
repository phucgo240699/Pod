#pragma once
#ifdef _AppController

#endif _AppController


#include<d3dx9math.h>
#include<string>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include"dxgraphics.h"
#include"Man1.h"
#include"Keyboard.h"


// Read keyboard command
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)

class AppController {
	// Name of program
private:
	ViewController* rootViewController = new Man1();

public:

	// De Init
	~AppController();

	// Getter
	ViewController* getRootViewController();

	// Setter
	void setRootViewController(ViewController* _rootViewController);

	// Prototypes function
	int Game_Init(HWND hwnd);
	void Game_Run(HWND hwnd);
	void Game_End(HWND hwnd);
	void Handler_Keyboard(HWND hwnd);
};