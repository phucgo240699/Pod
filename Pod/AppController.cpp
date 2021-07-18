#include"AppController.h"

ViewController* AppController::getRootViewController()
{
	return this->rootViewController;
}

void AppController::setRootViewController(SceneName _sceneName)
{
	switch (Setting::getInstance()->getSceneName())
	{
	case WorldScene:
		//if (this->worldVC == NULL) {
		//	this->worldVC = new WorldVC();
		//}

		//if (this->sunnyVC != NULL) {
		//	this->sunnyVC->~SunnyVC();
		//}
		////delete sunnyVC;

		//this->rootViewController = this->worldVC;
		//this->rootViewController->viewDidLoad();

		delete rootViewController;
		this->rootViewController = new WorldVC();
		this->rootViewController->viewDidLoad();
		break;
	case SunnyScene:
		//if (this->sunnyVC == NULL) {
		//	this->sunnyVC = new SunnyVC();
		//	this->sunnyVC->viewDidLoad();
		//}

		//if (this->worldVC != NULL) {
		//	this->worldVC->~WorldVC();
		//}
		////delete worldVC;

		//this->rootViewController = sunnyVC;
		//this->rootViewController->viewDidLoad();

		delete rootViewController;
		this->rootViewController = new SunnyVC();
		this->rootViewController->viewDidLoad();
		break;
	default:
		break;
	}
}

int AppController::Game_Init(HWND hwnd)
{
	this->setRootViewController(Setting::getInstance()->getSceneName());
	return 1;
}

void AppController::Game_Run(HWND hwnd, float _dt)
{
	if (Setting::getInstance()->getIsTransfering() == true) {
		Setting::getInstance()->setIsTransfering(false);
		this->setRootViewController(Setting::getInstance()->getSceneName());
	}

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

	// F3
	if (KEY_DOWN(VK_F3) == 1) {
		hasKeyDown = true;
		keyDowns.push_back(KeyType::F3);
	}
	else {
		keyUps.push_back(KeyType::F3);
	}

	// F4
	if (KEY_DOWN(VK_F4) == 1) {
		hasKeyDown = true;
		keyDowns.push_back(KeyType::F4);
	}
	else {
		keyUps.push_back(KeyType::F4);
	}

	// Enter
	if (KEY_DOWN(VK_RETURN) == 1) {
		keyDowns.push_back(KeyType::enter);
		hasKeyDown = true;
	}
	else {
		keyUps.push_back(KeyType::enter);
	}

	// Key A
	if (KEY_DOWN(0x41) == 1) {
		keyDowns.push_back(KeyType::key_A);
		hasKeyDown = true;
	}
	else {
		keyUps.push_back(KeyType::key_A);
	}

	// Key S
	if (KEY_DOWN(0x53) == 1) {
		keyDowns.push_back(KeyType::key_S);
		hasKeyDown = true;
	}
	else {
		keyUps.push_back(KeyType::key_S);
	}

	// Key D
	if (KEY_DOWN(0x44) == 1) {
		keyDowns.push_back(KeyType::key_D);
		hasKeyDown = true;
	}
	else {
		keyUps.push_back(KeyType::key_D);
	}

	// Up
	if (KEY_DOWN(VK_UP) == 1) {
		keyDowns.push_back(KeyType::up);
		hasKeyDown = true;
	}
	else {
		keyUps.push_back(KeyType::up);
	}

	// Down
	if (KEY_DOWN(VK_DOWN) == 1) {
		keyDowns.push_back(KeyType::down);
		hasKeyDown = true;
	}
	else {
		keyUps.push_back(KeyType::down);
	}

	// Left
	if (KEY_DOWN(VK_LEFT) == 1) {
		keyDowns.push_back(KeyType::left);
		hasKeyDown = true;
	}
	else {
		keyUps.push_back(KeyType::left);
	}

	// Right
	if (KEY_DOWN(VK_RIGHT) == 1) {
		keyDowns.push_back(KeyType::right);
		hasKeyDown = true;
	}
	else {
		keyUps.push_back(KeyType::right);
	}

	//// SPACE
	//if (KEY_DOWN(VK_SPACE) == 1) {
	//	keyDowns.push_back(KeyType::space);
	//	hasKeyDown = true;
	//}
	//else {
	//	keyUps.push_back(KeyType::space);
	//}

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
