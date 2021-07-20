#include "ViewController.h"
#include "AppController.h"

void ViewController::navigateTo(SceneName _sceneName)
{
	switch (_sceneName)
	{
	case SceneName::WorldScene:
	{
		break;
	}

	case SceneName::SunnyScene:
	{
		if (this->appController->getSceneName() == SceneName::WorldScene) {
			this->appController->setSunnyVC(new SunnyVC());
			this->appController->getSunnyVC()->viewDidLoad();
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
