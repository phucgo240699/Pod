#include"AppController.h"

//ViewController* AppController::getRootViewController()
//{
//	return this->rootViewController;
//}
//
//void AppController::setRootViewController(SceneName _sceneName)
//{
//	switch (Setting::getInstance()->getSceneName())
//	{
//	case WorldScene:
//		delete rootViewController;
//		this->rootViewController = new WorldVC();
//		this->rootViewController->viewDidLoad();
//		break;
//	case SunnyScene:
//		delete rootViewController;
//		this->rootViewController = new SunnyVC();
//		this->rootViewController->viewDidLoad();
//		break;
//	default:
//		break;
//	}
//}

SceneName AppController::getSceneName()
{
	return this->sceneName;
}

WorldVC* AppController::getWorldVC()
{
	return this->worldVC;
}

SunnyVC* AppController::getSunnyVC()
{
	return this->sunnyVC;
}

UndergroundVC* AppController::getUndergroundVC()
{
	return this->undergroundVC;
}

int AppController::Game_Init(HWND hwnd)
{
	//this->setRootViewController(Setting::getInstance()->getSceneName());
	AnimationBundle::getInstance()->load();
	this->setWorldVC(new WorldVC());
	this->getWorldVC()->viewDidLoad();

	ScoreBoard::getInstance()->resetTimeToZero();
	Camera::getInstance()->loadWorldMap();

	this->setUndergroundVC(new UndergroundVC());
	this->getUndergroundVC()->viewDidLoad();

	return 1;
}

void AppController::Game_Run(HWND hwnd, float _dt)
{
	/*if (Setting::getInstance()->getIsTransfering() == true) {
		Setting::getInstance()->setIsTransfering(false);
		this->setRootViewController(Setting::getInstance()->getSceneName());
	}

	this->rootViewController->viewWillUpdate(_dt);
	this->rootViewController->viewDidUpdate(_dt);
	this->rootViewController->viewWillRender();
	this->rootViewController->viewDidRender();*/


	// WorldScene
	if (this->getSceneName() == WorldScene) {
		this->getWorldVC()->viewWillUpdate(_dt);
		if (this->getSceneName() != WorldScene) return;
		this->getWorldVC()->viewDidUpdate(_dt);
		if (this->getSceneName() != WorldScene) return;
		this->getWorldVC()->viewWillRender();
		if (this->getSceneName() != WorldScene) return;
		this->getWorldVC()->viewDidRender();
	}

	// SunnyScene
	else if (this->getSceneName() == SunnyScene) {
		this->getSunnyVC()->viewWillUpdate(_dt);
		if (this->getSceneName() != SunnyScene) return;
		this->getSunnyVC()->viewDidUpdate(_dt);
		if (this->getSceneName() != SunnyScene) return;
		this->getSunnyVC()->viewWillRender();
		if (this->getSceneName() != SunnyScene) return;
		this->getSunnyVC()->viewDidRender();
	}
	
	// UndergroundScene
	else if (this->getSceneName() == UndergroundScene) {
		this->getUndergroundVC()->viewWillUpdate(_dt);
		if (this->getSceneName() != UndergroundScene) return;
		this->getUndergroundVC()->viewDidUpdate(_dt);
		if (this->getSceneName() != UndergroundScene) return;
		this->getUndergroundVC()->viewWillRender();
		if (this->getSceneName() != UndergroundScene) return;
		this->getUndergroundVC()->viewDidRender();
	}
}

void AppController::setSceneName(SceneName _sceneName)
{
	this->sceneName = _sceneName;
}

void AppController::setWorldVC(WorldVC* _worldVC)
{
	this->worldVC = _worldVC;
	this->worldVC->setAppController(this);
}

void AppController::setSunnyVC(SunnyVC* _sunnyVC)
{
	this->sunnyVC = _sunnyVC;
	this->sunnyVC->setAppController(this);
}

void AppController::setUndergroundVC(UndergroundVC* _undergroundVC)
{
	this->undergroundVC = _undergroundVC;
	this->undergroundVC->setAppController(this);
}

void AppController::Game_End(HWND hwnd)
{
	//this->rootViewController->viewWillRelease();

	if (this->getSceneName() == WorldScene) {
		this->getWorldVC()->viewWillRelease();
	}
	else if (this->getSceneName() == SunnyScene) {
		this->getSunnyVC()->viewWillRelease();
	}
	else if (this->getSceneName() ==  UndergroundScene) {
		this->getUndergroundVC()->viewWillRelease();
	}
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



	if (keyDowns.size() > 0) {
		//this->rootViewController->viewReceiveKeyDown(keyDowns);

		if (this->getSceneName() == WorldScene) {
			this->getWorldVC()->viewReceiveKeyDown(keyDowns);
		}
		else if (this->getSceneName() == SunnyScene) {
			this->getSunnyVC()->viewReceiveKeyDown(keyDowns);
		}
		else if (this->getSceneName() == UndergroundScene) {
			this->getUndergroundVC()->viewReceiveKeyDown(keyDowns);
		}
	}
	if (keyUps.size() > 0) {
		//this->rootViewController->viewReceiveKeyUp(keyUps);

		if (this->getSceneName() == WorldScene) {
			this->getWorldVC()->viewReceiveKeyUp(keyUps);
		}
		else if (this->getSceneName() == SunnyScene) {
			this->getSunnyVC()->viewReceiveKeyUp(keyUps);
		}
		else if (this->getSceneName() == UndergroundScene) {
			this->getUndergroundVC()->viewReceiveKeyUp(keyUps);
		}
	}
	if (!hasKeyDown) {
		//this->rootViewController->viewReceiveKeyUp();

		if (this->getSceneName() == WorldScene) {
			this->getWorldVC()->viewReceiveKeyUp();
		}
		else if (this->getSceneName() == SunnyScene) {
			this->getSunnyVC()->viewReceiveKeyUp();
		}
		else if (this->getSceneName() == UndergroundScene) {
			this->getUndergroundVC()->viewReceiveKeyUp();
		}
	}
}
