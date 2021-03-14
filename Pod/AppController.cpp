#include"AppController.h"


ViewController* AppController::getRootViewController()
{
	return this->rootViewController;
}

void AppController::setRootViewController(ViewController* _rootViewController)
{
	this->rootViewController = _rootViewController;
}

int AppController::Game_Init(HWND)
{


	this->rootViewController->viewDidLoad();
	return 1;
}

void AppController::Game_Run(HWND)
{
	this->rootViewController->viewWillUpdate();
	this->rootViewController->viewDidUpdate();
	this->rootViewController->viewWillRender();
	this->rootViewController->viewDidRender();
}

void AppController::Game_End(HWND)
{
	this->rootViewController->viewWillRelease();
}