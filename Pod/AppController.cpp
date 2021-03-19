#include"AppController.h"


AppController::~AppController()
{
	delete rootViewController;
}

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
	Handler_Keyboard(hwnd);

	this->rootViewController->viewWillUpdate();
	this->rootViewController->viewDidUpdate();
	this->rootViewController->viewWillRender();
	this->rootViewController->viewDidRender();
}

void AppController::Game_End(HWND hwnd)
{
	this->rootViewController->viewWillRelease();
}

void AppController::Handler_Keyboard(HWND hwnd)
{
	// Escape
	if (KEY_DOWN(VK_ESCAPE) == 1) {
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}

	// Up
	if (KEY_DOWN(VK_UP) == 1) {
		this->rootViewController->viewReceiveKeyDown(KeyType::up);
	}
	if (KEY_UP(VK_UP) == 0) {
		this->rootViewController->viewReceiveKeyUp(KeyType::up);
	}

	// Down
	if (KEY_DOWN(VK_DOWN) == 1) {
		this->rootViewController->viewReceiveKeyDown(KeyType::down);
	}
	if (KEY_UP(VK_DOWN) == 0) {
		this->rootViewController->viewReceiveKeyUp(KeyType::down);
	}

	// Left
	if (KEY_DOWN(VK_LEFT) == 1) {
		this->rootViewController->viewReceiveKeyDown(KeyType::left);
	}
	if (KEY_UP(VK_LEFT) == 0) {
		this->rootViewController->viewReceiveKeyUp(KeyType::left);
	}

	// Right
	if (KEY_DOWN(VK_RIGHT) == 1) {
		this->rootViewController->viewReceiveKeyDown(KeyType::right);
	}
	if (KEY_UP(VK_RIGHT) == 0) {
		this->rootViewController->viewReceiveKeyUp(KeyType::right);
	}
}
