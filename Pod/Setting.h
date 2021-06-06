#pragma once
#include "Tool.h"
#include "FileManager.h"
#include "string"
#include "SectionFile.h"
#include "SceneName.h"

using namespace std;

enum ScreenMode {
	window,		// 0
	fullScreen	// 1
};

// Singleton
class Setting {
private:
	Setting() = default; // 1.Don't public constructor function
	static Setting* instance; // 2. static private instance

	// Properties
	float dt = 1;
	int fps = 30;
	int screenWidth = 640;
	int screenHeight = 480;
	ScreenMode screenMode = window;
	Color* defaultBackgroundColorViewController = new Color(black);
	bool debugMode = false;
	SceneName sceneName = WorldScene;

public:
	Setting(const Setting&) = delete; // 3. delete copy constructor
	static Setting* getInstance();	  // 4. public function for client code usage

	// Getter
	float getDt();
	int getFPS();
	int getScreenWidth();
	int getScreenHeight();
	ScreenMode getScreenMode();
	Color* getDefaultBackgroundColorViewController();
	bool getDebugMode();
	SceneName getSceneName();

	// Setter
	void setDt(float _dt);
	void setFPS(int _fps);
	void setScreenWidth(int _width);
	void setScreenHeight(int _height);
	void setScreenMode(ScreenMode _screenMode);
	void setDefaultBackgroundColorViewController(Color* _color);
	void setDebugMode(bool _debugMode);
	void setSceneName(SceneName _sceneName);

	void toggleDebugMode();

	// Others
	//void save();
	void load();
	//void load(string line, char seperator);
};