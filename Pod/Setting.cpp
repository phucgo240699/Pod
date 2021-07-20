#include "Setting.h"

Setting* Setting::instance;

Setting* Setting::getInstance()
{
	if (Setting::instance == nullptr) {
		instance = new Setting();
		instance->load();
	}
	return instance;
}

int Setting::getFPS()
{
	return this->fps;
}

ScreenMode Setting::getScreenMode()
{
	return this->screenMode;
}

int Setting::getScreenWidth()
{
	return this->screenWidth;
}

int Setting::getScreenHeight()
{
	return this->screenHeight;
}

float Setting::getDt()
{
	return this->dt;
}

void Setting::setFPS(int _fps)
{
	if (_fps > 0) {
		this->fps = _fps;
	}
}

Color* Setting::getDefaultBackgroundColorViewController()
{
	return this->defaultBackgroundColorViewController;
}

bool Setting::getDebugMode()
{
	return this->debugMode;
}

//SceneName Setting::getSceneName()
//{
//	return this->sceneName;
//}

//bool Setting::getIsTransfering()
//{
//	return this->isTransfering;
//}

float Setting::getCollisionSafeSpace()
{
	return this->collisionSafeSpace;
}

void Setting::setScreenMode(ScreenMode _screenMode)
{
	this->screenMode = _screenMode;
}

void Setting::setScreenWidth(int _width)
{
	this->screenWidth = _width;
}

void Setting::setScreenHeight(int _height)
{
	this->screenHeight = _height;
}

void Setting::setDt(float _dt)
{
	this->dt = _dt;
}

void Setting::setDefaultBackgroundColorViewController(Color* _color)
{
	this->defaultBackgroundColorViewController = _color;
}

void Setting::setDebugMode(bool _debugMode)
{
	this->debugMode = _debugMode;
}

//void Setting::setSceneName(SceneName _sceneName)
//{
//	this->sceneName = _sceneName;
//}

//void Setting::setIsTransfering(int _isTransfering)
//{
//	this->isTransfering = _isTransfering;
//}

void Setting::toggleDebugMode()
{
	this->debugMode = !(this->debugMode);
}

void Setting::setCollisionSafeSpace(float _value)
{
	this->collisionSafeSpace = _value;
}

void Setting::load()
{
	fstream fs;
	fs.open(FilePath::getInstance()->settings, ios::in);
	string line;
	SectionFileType section = SECTION_NONE;
	vector<string> v;

	while (!fs.eof()) {
		getline(fs, line);

		if (line == "" || line[0] == '#') continue;

		v = Tool::splitToVectorStringFrom(line, ',');

		this->setDt(stof(v[0]));
		this->setFPS(stof(v[1]));
		this->setScreenWidth(stoi(v[2]));
		this->setScreenHeight(stoi(v[3]));
		this->setScreenMode(v[4] == "0" ? window : fullScreen);
		this->setDefaultBackgroundColorViewController(new Color(Tool::getColorFromString(v[5])));
		this->setDebugMode(v[6] == "1" ? true : false);
		this->setCollisionSafeSpace(stoi(v[7]));

		/*if (v[8] == "SunnyScene") {
			setSceneName(SceneName::SunnyScene);
		}
		else {
			setSceneName(SceneName::WorldScene);
		}*/
	}

	fs.close();
}