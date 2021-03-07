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

LPCWSTR Setting::getAppTitle()
{
	return this->appTitle;
}

Size* Setting::getScreenSize()
{
	return this->screenSize;
}

ScreenMode Setting::getScreenMode()
{
	return this->screenMode;
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
	this->appTitle = Tool::getLPCWSTRFrom(_appTitle);
}

void Setting::setAppTitle(LPCWSTR _appTitle)
{
	this->appTitle = _appTitle;
}

void Setting::setScreenSize(Size* _screenSize)
{
	this->screenSize = _screenSize;
}

void Setting::setScreenMode(ScreenMode _screenMode)
{
	this->screenMode = _screenMode;
}

void Setting::setBackBufferColor(Color* _backBufferColor)
{
	this->backBufferColor = _backBufferColor;
}

void Setting::load()
{
	string settingsStr = FileManager::getInstance()->getStringFromTextFile("settings.txt");
	vector<string> v = Tool::splitToVectorStringFrom(settingsStr, ',');
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << endl;
	}
}

void Setting::save()
{
	string settingsStr = "";
	settingsStr += to_string(this->fps);
	settingsStr += (',' + Tool::getStringFrom(appTitle));
	settingsStr += (',' + string((this->screenMode == window) ? "0" : "1")); // 0: window		1: fullscreen
	settingsStr += (',' + Tool::getStringFromColor(this->backBufferColor->getValue()));

	FileManager::getInstance()->writeStringToTextFile("settings.txt", settingsStr);
}
