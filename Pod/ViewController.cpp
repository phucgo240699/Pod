#include "ViewController.h"
#include "AppController.h"

void ViewController::navigateTo(SceneName _sceneName)
{
	switch (_sceneName)
	{
	case SceneName::WorldScene:
	{
		ScoreBoard::getInstance()->resetTimeToZero();
		Camera::getInstance()->loadWorldMap();
		break;
	}

	case SceneName::UndergroundScene:
	{
		Camera::getInstance()->loadUndergroundMap();
		Grid::getInstance()->loadUnderGroundMap();
		this->appController->getUndergroundVC()->adaptToGrid();
		break;
	}

	case SceneName::SunnyScene:
	{
		if (this->appController->getSceneName() == SceneName::WorldScene) {
			this->appController->setSunnyVC(new SunnyVC());
			ScoreBoard::getInstance()->resetTimeTo300();
			Camera::getInstance()->loadSunnyMap();
			Grid::getInstance()->loadSunnyMap();
			this->appController->getSunnyVC()->viewDidLoad();
			this->appController->getSunnyVC()->adaptToGrid();
			Camera::getInstance()->setPositionBy(this->appController->getSunnyVC()->getMario());
		}
		else if (this->appController->getSceneName() == SceneName::UndergroundScene) {
			Camera::getInstance()->loadSunnyMap();

			//this->appController->getSunnyVC()->setMario(new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING));
			this->appController->getSunnyVC()->getMario()->load();
			this->appController->getSunnyVC()->getMario()->setX(this->appController->getSunnyVC()->getLeftAnchorMarioPoppingUpFromPipe());
			this->appController->getSunnyVC()->getMario()->setY(this->appController->getSunnyVC()->getBottomAnchorMarioPoppingUpFromPipe());
			this->appController->getSunnyVC()->getMario()->setLimitX(Camera::getInstance()->getLimitX());
			this->appController->getSunnyVC()->getMario()->setLimitY(Camera::getInstance()->getLimitY());

			Camera::getInstance()->setPositionBy(this->appController->getSunnyVC()->getMario());

			Grid::getInstance()->loadSunnyMap();
			this->appController->getSunnyVC()->adaptToGrid();

			//this->appController->getSunnyVC()->getMario()->setAnimation(new Animation(AnimationBundle::getInstance()->getMarioStanding()));
			this->appController->getSunnyVC()->getMario()->setState(MarioState::POPPING_UP_PIPE);
			this->appController->getSunnyVC()->getMario()->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
			this->appController->getSunnyVC()->getMario()->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));


		}
		break;
	}

	case ThirdScene:
	{
		if (this->appController->getSceneName() == SceneName::WorldScene) {
			this->appController->setThirdVC(new ThirdVC());
			ScoreBoard::getInstance()->resetTimeTo300();
			Camera::getInstance()->loadThirdMap();
			Grid::getInstance()->loadThirdMap();
			this->appController->getThirdVC()->viewDidLoad();
			this->appController->getThirdVC()->adaptToGrid();
			Camera::getInstance()->setPositionBy(this->appController->getThirdVC()->getMario());
		}

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

void ViewController::viewReceiveKeyUp()
{
}

void ViewController::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
}

void ViewController::viewWillUpdate(float _dt)
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
