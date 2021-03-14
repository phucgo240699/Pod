#include"AppController.h"


ViewController* AppController::getRootViewController()
{
	return this->rootViewController;
}

void AppController::setRootViewController(ViewController* _rootViewController)
{
	this->rootViewController = _rootViewController;
}

int AppController::Game_Init(HWND hwnd)
{


	this->rootViewController->viewDidLoad();
	return 1;
}

void AppController::Game_Run(HWND hwnd)
{
	if (KEY_DOWN(VK_ESCAPE)) {
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}

	this->rootViewController->viewWillUpdate();
	this->rootViewController->viewDidUpdate();
	this->rootViewController->viewWillRender();
	this->rootViewController->viewDidRender();
}

void AppController::Game_End(HWND hwnd)
{
	this->rootViewController->viewWillRelease();
}