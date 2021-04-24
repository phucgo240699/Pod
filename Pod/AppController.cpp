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

void AppController::Game_Run(HWND hwnd, float _dt)
{
	Handler_Keyboard(hwnd);

	this->rootViewController->viewWillUpdate(_dt);
	this->rootViewController->viewDidUpdate(_dt);
	this->rootViewController->viewWillRender();
	this->rootViewController->viewDidRender();
}

void AppController::Game_End(HWND hwnd)
{
	this->rootViewController->viewWillRelease();
}

void AppController::Handler_Keyboard(HWND hwnd)
{
	bool hasKeyDown = false;
	// Escape
	if (KEY_DOWN(VK_ESCAPE) == 1) {
		PostMessage(hwnd, WM_DESTROY, 0, 0);
		hasKeyDown = true;
	}

	// Up
	if (KEY_DOWN(VK_UP) == 1) {
		this->rootViewController->viewReceiveKeyDown(KeyType::up);
		hasKeyDown = true;
	}

	// Down
	if (KEY_DOWN(VK_DOWN) == 1) {
		this->rootViewController->viewReceiveKeyDown(KeyType::down);
		hasKeyDown = true;
	}

	// Left
	if (KEY_DOWN(VK_LEFT) == 1) {
		this->rootViewController->viewReceiveKeyDown(KeyType::left);
		hasKeyDown = true;
	}

	// Right
	if (KEY_DOWN(VK_RIGHT) == 1) {
		this->rootViewController->viewReceiveKeyDown(KeyType::right);
		hasKeyDown = true;
	}

	// SPACE
	if (KEY_DOWN(VK_SPACE) == 1) {
		this->rootViewController->viewReceiveKeyDown(KeyType::space);
		hasKeyDown = true;
	}

	if (!hasKeyDown) {
		this->rootViewController->viewReceiveKeyUp();
	}
}
