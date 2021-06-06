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

SceneName Setting::getSceneName()
{
	return this->sceneName;
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

void Setting::setSceneName(SceneName _sceneName)
{
	this->sceneName = _sceneName;
}

void Setting::toggleDebugMode()
{
	this->debugMode = !(this->debugMode);
}

void Setting::load()
{
	string filePath = "";

	switch (this->sceneName)
	{
	case WorldScene:
		filePath = FilePath::getInstance()->world_map;
		break;
	case SunnyScene:
		filePath = FilePath::getInstance()->sunny_map;
		break;
	default:
		break;
	}

	fstream fs;
	fs.open(filePath, ios::in);
	string line;
	SectionFileType section = SECTION_NONE;
	vector<string> v;

	while (!fs.eof()) {
		getline(fs, line);

		if (line == "" || line[0] == '#') continue;
		if (line == "<Settings>") {
			section = SECTION_SETTING;
			continue;
		}
		else if (line == "</Settings>") return;

		switch (section)
		{
		case SECTION_SETTING:
			v = Tool::splitToVectorStringFrom(line, ',');

			this->setDt(stof(v[0]));
			this->setFPS(stof(v[1]));
			this->setScreenWidth(stoi(v[2]));
			this->setScreenHeight(stoi(v[3]));
			this->setScreenMode(v[4] == "0" ? window : fullScreen);
			this->setDefaultBackgroundColorViewController(new Color(Tool::getColorFromString(v[5])));
			this->setDebugMode(v[6] == "1" ? true : false);
			
			break;
		default:
			break;
		}
	}

	fs.close();
}

//void Setting::load(string line, char seperator)
//{
//	vector<string> settings = Tool::splitToVectorStringFrom(line, seperator);
//	this->dt = stof(settings[0]);
//	this->fps = stoi(settings[1]);
//	this->screenWidth = stoi(settings[2]);
//	this->screenHeight = stoi(settings[3]);
//	this->screenMode = settings[4] == "0" ? window : fullScreen;
//	this->defaultBackgroundColorViewController = new Color(Tool::getColorFromString(settings[5]));
//	this->debugMode = settings[6] == "1" ? true : false;
//}

//void Setting::save()
//{
//	string settingsStr = "";
//	settingsStr += to_string(this->dt);
//	settingsStr += ',';
//	settingsStr += to_string(this->fps);
//	settingsStr += ",";
//	settingsStr += to_string(this->screenWidth);
//	settingsStr += ",";
//	settingsStr += to_string(this->screenHeight);
//	settingsStr += (',' + string((this->screenMode == window) ? "0" : "1")); // 0: window		1: fullscreen
//	settingsStr += (',' + Tool::getStringFromColor(this->defaultBackgroundColorViewController->getValue()));
//
//	FileManager::getInstance()->writeStringToTextFile(FilePath::getInstance()->setting, settingsStr);
//}

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
