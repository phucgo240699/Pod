#pragma once
#include "Tool.h"
#include "FileManager.h"

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


	// Setter
	void setDt(float _dt);
	void setFPS(int _fps);
	void setScreenWidth(int _width);
	void setScreenHeight(int _height);
	void setScreenMode(ScreenMode _screenMode);
	void setDefaultBackgroundColorViewController(Color* _color);

	// Others
	void save();
	void load();
	void load(string line, char seperator);
};