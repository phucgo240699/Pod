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

int Setting::getDt()
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

//string Setting::getRootImagesFolder()
//{
//	return this->rootImagesFolder;
//}
//
//string Setting::getRootSoundsFolder()
//{
//	return this->rootSoundsFolder;
//}
//
//string Setting::getRootTextFilesFolder()
//{
//	return this->rootTextFileFolder;
//}

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

void Setting::setDt(int _dt)
{
	this->dt = _dt;
}

void Setting::setDefaultBackgroundColorViewController(Color* _color)
{
	this->defaultBackgroundColorViewController = _color;
}

void Setting::load()
{
	string settingsStr = FileManager::getInstance()->getStringFromTextFile("settings.txt");
	vector<string> v = Tool::splitToVectorStringFrom(settingsStr, ',');
	
	this->dt = stoi(v[0]);
	this->fps = stoi(v[1]);
	this->screenWidth = stoi(v[2]);
	this->screenHeight = stoi(v[3]);
	this->screenMode = v[4] == "0" ? window : fullScreen;
	this->defaultBackgroundColorViewController = new Color(Tool::getColorFromString(v[5]));
}

void Setting::save()
{
	string settingsStr = "";
	settingsStr += to_string(this->dt);
	settingsStr += ',';
	settingsStr += to_string(this->fps);
	settingsStr += ",";
	settingsStr += to_string(this->screenWidth);
	settingsStr += ",";
	settingsStr += to_string(this->screenHeight);
	settingsStr += (',' + string((this->screenMode == window) ? "0" : "1")); // 0: window		1: fullscreen
	settingsStr += (',' + Tool::getStringFromColor(this->defaultBackgroundColorViewController->getValue()));

	FileManager::getInstance()->writeStringToTextFile("settings.txt", settingsStr);
}

//void Setting::setRootImagesFolder(string _path)
//{
//	this->rootImagesFolder = _path;
//}
//
//void Setting::setRootSoundsFolder(string _path)
//{
//	this->rootSoundsFolder = _path;
//}
//
//void Setting::setRootTextFilesFolder(string _path)
//{
//	this->rootTextFileFolder = _path;
//}
