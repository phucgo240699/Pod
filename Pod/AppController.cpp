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
	vector<KeyType> keyDowns = vector<KeyType>();
	vector<KeyType> keyUps = vector<KeyType>();

	bool hasKeyDown = false;
	// Escape
	if (KEY_DOWN(VK_ESCAPE) == 1) {
		PostMessage(hwnd, WM_DESTROY, 0, 0);
		hasKeyDown = true;
	}

	// Debug Mode
	if (KEY_DOWN(VK_F1) == 1) {
		Setting::getInstance()->setDebugMode(true);
		hasKeyDown = true;
	}
	if (KEY_DOWN(VK_F2) == 1) {
		Setting::getInstance()->setDebugMode(false);
		hasKeyDown = true;
	}

	// Up
	if (KEY_DOWN(VK_UP) == 1) {
		keyDowns.push_back(KeyType::up);
		hasKeyDown = true;
	}
	else if (KEY_DOWN(VK_UP) != 1) {
		keyUps.push_back(KeyType::up);
	}

	// Down
	if (KEY_DOWN(VK_DOWN) == 1) {
		keyDowns.push_back(KeyType::down);
		hasKeyDown = true;
	}
	else if (KEY_DOWN(VK_DOWN) != 1) {
		keyUps.push_back(KeyType::down);
	}

	// Right
	if (KEY_DOWN(VK_RIGHT) == 1) {
		keyDowns.push_back(KeyType::right);
		hasKeyDown = true;
	}
	else if (KEY_DOWN(VK_RIGHT) != 1) {
		keyUps.push_back(KeyType::right);
	}

	// Left
	if (KEY_DOWN(VK_LEFT) == 1) {
		keyDowns.push_back(KeyType::left);
		hasKeyDown = true;
	}
	else if (KEY_DOWN(VK_LEFT) != 1) {
		keyUps.push_back(KeyType::left);
	}

	// SPACE
	if (KEY_DOWN(VK_SPACE) == 1) {
		keyDowns.push_back(KeyType::space);
		hasKeyDown = true;
	}
	else if (KEY_DOWN(VK_SPACE) != 1) {
		keyUps.push_back(KeyType::space);
	}

	if (keyDowns.size() > 0) {
		this->rootViewController->viewReceiveKeyDown(keyDowns);
	}
	if (keyUps.size() > 0) {
		this->rootViewController->viewReceiveKeyUp(keyUps);
	}
	if (!hasKeyDown) {
		this->rootViewController->viewReceiveKeyUp();
	}
}
