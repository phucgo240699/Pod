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
		this->appController->setUndergroundVC(new UndergroundVC());
		Camera::getInstance()->loadUndergroundMap();
		Grid::getInstance()->loadUnderGroundMap();
		this->appController->getUndergroundVC()->viewDidLoad();
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
