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
	int fps = 30;
	int screenWidth = 640;
	int screenHeight = 480;
	ScreenMode screenMode = window;
	Color* defaultBackgroundColorViewController = new Color(black);
	/*string rootImagesFolder = "./Assets/Images/";
	string rootSoundsFolder = "./Assets/Sounds/";
	string rootTextFileFolder = "./Assets/TextFiles/";*/

public:
	Setting(const Setting&) = delete; // 3. delete copy constructor
	static Setting* getInstance();	  // 4. public function for client code usage

	// Getter
	int getFPS();
	int getScreenWidth();
	int getScreenHeight();
	ScreenMode getScreenMode();
	Color* getDefaultBackgroundColorViewController();
	/*string getRootImagesFolder();
	string getRootSoundsFolder();
	string getRootTextFilesFolder();*/


	// Setter
	void setFPS(int _fps);
	void setScreenWidth(int _width);
	void setScreenHeight(int _height);
	void setScreenMode(ScreenMode _screenMode);
	void setDefaultBackgroundColorViewController(Color* _color);
	/*void setRootImagesFolder(string _path);
	void setRootSoundsFolder(string _path);
	void setRootTextFilesFolder(string _path);*/

	// Others
	void save();
	void load();
};