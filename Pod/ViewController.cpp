#include "ViewController.h"
#include "AppController.h"

void ViewController::navigateTo(SceneName _sceneName)
{
	switch (_sceneName)
	{
	case SceneName::WorldScene:
	{
		if (this->appController->getSceneName() == _sceneName) {
			return;
		}

		ScoreBoard::getInstance()->resetTimeToZero();
		Camera::getInstance()->loadWorldMap();
		if (this->appController->getSceneName() == SunnyScene) {
			this->appController->getWorldVC()->getWMario()->setIsFireMode(this->appController->getSunnyVC()->getMario()->getIsFireMode());
			this->appController->getWorldVC()->getWMario()->setIsSuperMode(this->appController->getSunnyVC()->getMario()->getIsSuperMode());
			this->appController->getWorldVC()->getWMario()->setIsFlyingMode(this->appController->getSunnyVC()->getMario()->getIsFlyingMode());
			this->appController->getSunnyVC()->getMario()->save();
		}
		else if (this->appController->getSceneName() == UndergroundScene) {
			this->appController->getWorldVC()->getWMario()->setIsFireMode(this->appController->getUndergroundVC()->getMario()->getIsFireMode());
			this->appController->getWorldVC()->getWMario()->setIsSuperMode(this->appController->getUndergroundVC()->getMario()->getIsSuperMode());
			this->appController->getWorldVC()->getWMario()->setIsFlyingMode(this->appController->getUndergroundVC()->getMario()->getIsFlyingMode());
			this->appController->getUndergroundVC()->getMario()->save();
		}
		else if (this->appController->getSceneName() == ThirdScene) {
			this->appController->getWorldVC()->getWMario()->setIsFireMode(this->appController->getThirdVC()->getMario()->getIsFireMode());
			this->appController->getWorldVC()->getWMario()->setIsSuperMode(this->appController->getThirdVC()->getMario()->getIsSuperMode());
			this->appController->getWorldVC()->getWMario()->setIsFlyingMode(this->appController->getThirdVC()->getMario()->getIsFlyingMode());
			this->appController->getThirdVC()->getMario()->save();
		}
		else if (this->appController->getSceneName() == CloudyScene) {
			this->appController->getWorldVC()->getWMario()->setIsFireMode(this->appController->getCloudyVC()->getMario()->getIsFireMode());
			this->appController->getWorldVC()->getWMario()->setIsSuperMode(this->appController->getCloudyVC()->getMario()->getIsSuperMode());
			this->appController->getWorldVC()->getWMario()->setIsFlyingMode(this->appController->getCloudyVC()->getMario()->getIsFlyingMode());
			this->appController->getCloudyVC()->getMario()->save();
		}

		this->appController->setUndergroundVC(new UndergroundVC());
		this->appController->getUndergroundVC()->viewDidLoad();

		this->appController->setCloudyVC(new CloudyVC());
		this->appController->getCloudyVC()->viewDidLoad();

		break;
	}

	case SceneName::UndergroundScene:
	{
		if (this->appController->getSceneName() == _sceneName) {
			return;
		}

		// If current scene is SunnyScene => Save Current Grid Sunny Map, and save mario
		if (this->appController->getSceneName() == SunnyScene) {
			Grid::getInstance()->saveCurrentSunnyMap();
			this->appController->getSunnyVC()->getMario()->save();
		}

		Camera::getInstance()->loadUndergroundMap();
		Grid::getInstance()->loadOriginalUnderGroundMap();
		this->appController->getUndergroundVC()->adaptToGrid();
		this->appController->getUndergroundVC()->getMario()->load();
		this->appController->getUndergroundVC()->getMario()->setX(float(136));
		this->appController->getUndergroundVC()->getMario()->setY(float(48));
		this->appController->getUndergroundVC()->getMario()->setState(MarioState::DROPPING);
		Camera::getInstance()->setPositionBy(this->appController->getUndergroundVC()->getMario());
		this->appController->getUndergroundVC()->getMario()->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
		this->appController->getUndergroundVC()->getMario()->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));
		break;
	}

	case SceneName::SunnyScene:
	{
		if (this->appController->getSceneName() == _sceneName) {
			return;
		}

		if (this->appController->getSceneName() == SceneName::WorldScene) {
			this->appController->setSunnyVC(new SunnyVC());
			ScoreBoard::getInstance()->resetTimeTo300();
			Camera::getInstance()->loadSunnyMap();
			Grid::getInstance()->loadOriginalSunnyMap();
			this->appController->getSunnyVC()->viewDidLoad();
			this->appController->getSunnyVC()->adaptToGrid();
			Camera::getInstance()->setPositionBy(this->appController->getSunnyVC()->getMario());
		}
		else if (this->appController->getSceneName() == SceneName::UndergroundScene) {
			// If current scene is UndergroundScene => Save  mario
			this->appController->getUndergroundVC()->getMario()->save();
			
			Camera::getInstance()->loadSunnyMap();

			//this->appController->getSunnyVC()->setMario(new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING));
			this->appController->getSunnyVC()->getMario()->load();
			this->appController->getSunnyVC()->getMario()->setX(this->appController->getSunnyVC()->getLeftAnchorMarioPoppingUpFromPipe());
			this->appController->getSunnyVC()->getMario()->setY(this->appController->getSunnyVC()->getBottomAnchorMarioPoppingUpFromPipe());
			this->appController->getSunnyVC()->getMario()->setLimitX(Camera::getInstance()->getLimitX());
			this->appController->getSunnyVC()->getMario()->setLimitY(Camera::getInstance()->getLimitY());

			Camera::getInstance()->setPositionBy(this->appController->getSunnyVC()->getMario());

			Grid::getInstance()->loadCurrentSunnyMap();
			this->appController->getSunnyVC()->adaptToGrid();

			//this->appController->getSunnyVC()->getMario()->setAnimation(new Animation(AnimationBundle::getInstance()->getMarioStanding()));
			this->appController->getSunnyVC()->getMario()->setState(MarioState::POPPING_UP_PIPE);
			this->appController->getSunnyVC()->getMario()->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
			this->appController->getSunnyVC()->getMario()->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));
		}
		break;
	}

	case SceneName::ThirdScene:
	{
		if (this->appController->getSceneName() == _sceneName) {
			return;
		}

		if (this->appController->getSceneName() == SceneName::WorldScene) {
			this->appController->setThirdVC(new ThirdVC());
			ScoreBoard::getInstance()->resetTimeTo300();
			Camera::getInstance()->loadThirdMap();
			Grid::getInstance()->loadOriginalThirdMap();
			this->appController->getThirdVC()->viewDidLoad();
			this->appController->getThirdVC()->adaptToGrid();
			Camera::getInstance()->setPositionBy(this->appController->getThirdVC()->getMario());
		}
		else if (this->appController->getSceneName() == SceneName::CloudyScene) {
			// If current scene is CloudyScene => Save  mario
			this->appController->getCloudyVC()->getMario()->save();
			
			Camera::getInstance()->loadThirdMap();

			this->appController->getThirdVC()->getMario()->load();
			this->appController->getThirdVC()->getMario()->setX(float(this->appController->getThirdVC()->getLeftAnchorDroppingFromCloudy()));
			this->appController->getThirdVC()->getMario()->setY(float(this->appController->getThirdVC()->getTopAnchorDroppingFromCloudy()));
			this->appController->getThirdVC()->getMario()->setLimitX(Camera::getInstance()->getLimitX());
			this->appController->getThirdVC()->getMario()->setLimitY(Camera::getInstance()->getLimitY());

			Camera::getInstance()->setPositionBy(this->appController->getThirdVC()->getMario());

			Grid::getInstance()->loadCurrentThirdMap();
			this->appController->getThirdVC()->adaptToGrid();

			//this->appController->getThirdVC()->getMario()->setAnimation(new Animation(AnimationBundle::getInstance()->getMarioStanding()));
			this->appController->getThirdVC()->getMario()->setState(MarioState::DROPPING);
			this->appController->getThirdVC()->getMario()->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
			this->appController->getThirdVC()->getMario()->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));
		}

		break;
	}

	case SceneName::CloudyScene:
	{
		if (this->appController->getSceneName() == _sceneName) {
			return;
		}

		// If current scene is SunnyScene => Save Current Grid Sunny Map, and save mario
		if (this->appController->getSceneName() == ThirdScene) {
			Grid::getInstance()->saveCurrentThirdMap();
			this->appController->getThirdVC()->getMario()->save();
		}

		Camera::getInstance()->loadCloudyMap();
		Grid::getInstance()->loadOriginalCloudyMap();
		this->appController->getCloudyVC()->adaptToGrid();
		this->appController->getCloudyVC()->getMario()->load();

		this->appController->getCloudyVC()->getMario()->setX(float(134));
		this->appController->getCloudyVC()->getMario()->setY(float(380));
		this->appController->getCloudyVC()->getMario()->setState(MarioState::JUMPING);
		Camera::getInstance()->setPositionBy(this->appController->getCloudyVC()->getMario());

		this->appController->getCloudyVC()->getMario()->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
		this->appController->getCloudyVC()->getMario()->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));
		break;
	}
	default:
		break;
	}

	this->appController->setSceneName(_sceneName);
}

void ViewController::setAppController(AppController* _appController)
{
	this->appController = _appController;
}

void ViewController::viewDidLoad()
{
}

void ViewController::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
}

void ViewController::viewWillUpdate(float _dt)
{
}

void ViewController::viewReceiveKeyUp()
{
}

void ViewController::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
}

void ViewController::viewUpdate(float _dt)
{
}

void ViewController::viewDidUpdate(float _dt)
{
}

void ViewController::viewWillRender()
{
}

void ViewController::viewDidRender()
{
}

void ViewController::viewWillRelease()
{
}
