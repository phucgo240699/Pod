#include "Setting.h"

Setting* Setting::instance;

Setting* Setting::getInstance()
{
	if (Setting::instance == nullptr) {
		instance = new Setting();
	}
	return instance;
}

int Setting::getFPS()
{
	return this->fps;
}

string Setting::getAppTitle()
{
	return this->appTitle;
}

LPCWSTR Setting::getAppTitleAsLPCWSTR()
{
	return Tool::getLPCWSTRFromString(this->appTitle);
}

ScreenMode Setting::getScreenMode()
{
	return this->screenMode;
}

Size* Setting::getScreenSize()
{
	return this->screenSize;
}

Color* Setting::getBackBufferColor()
{
	return this->backBufferColor;
}

void Setting::setFPS(int _fps)
{
	if (_fps > 0) {
		this->fps = _fps;
	}
}

void Setting::setAppTitle(string _appTitle)
{
	this->appTitle = _appTitle;
}

Color* Setting::getDefaultBackgroundColorViewController()
{
	return this->defaultBackgroundColorViewController;
}

void Setting::setScreenMode(ScreenMode _screenMode)
{
	this->screenMode = _screenMode;
}

void Setting::setScreenSize(Size* _screenSize)
{
	this->screenSize = _screenSize;
}

void Setting::setBackBufferColor(Color* _backBufferColor)
{
	this->backBufferColor = _backBufferColor;
}

void Setting::setDefaultBackgroundColorViewController(Color* _color)
{
	this->defaultBackgroundColorViewController = _color;
}

void Setting::load()
{
	string settingsStr = FileManager::getInstance()->getStringFromTextFile("settings.txt");
	vector<string> v = Tool::splitToVectorStringFrom(settingsStr, ',');
	
	this->fps = stoi(v[0]);
	this->appTitle = v[1];
	this->screenMode = v[2] == "0" ? window : fullScreen;
	this->screenSize = new Size(stoi(v[3]), stoi(v[4]));
	this->backBufferColor = new Color(Tool::getColorFromString(v[5]));
	this->defaultBackgroundColorViewController = new Color(Tool::getColorFromString(v[6]));
}

void Setting::save()
{
	string settingsStr = "";
	settingsStr += to_string(this->fps);
	settingsStr += (',' + this->appTitle);
	settingsStr += (',' + string((this->screenMode == window) ? "0" : "1")); // 0: window		1: fullscreen
	settingsStr += (',' + to_string(this->screenSize->getWidth()) + ',' + to_string(this->screenSize->getHeight()));
	settingsStr += (',' + Tool::getStringFromColor(this->backBufferColor->getValue()));
	settingsStr += (',' + Tool::getStringFromColor(this->defaultBackgroundColorViewController->getValue()));

	FileManager::getInstance()->writeStringToTextFile("settings.txt", settingsStr);
}
