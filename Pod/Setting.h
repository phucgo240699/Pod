#pragma once
#include "Size.h"
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
	string appTitle = "Pod";
	ScreenMode screenMode = window;
	Size* screenSize = new Size(480, 640);
	Color* backBufferColor = new Color(black);

public:
	Setting(const Setting&) = delete; // 3. delete copy constructor
	static Setting* getInstance();	  // 4. public function for client code usage

	// Getter
	int getFPS();
	string getAppTitle();
	LPCWSTR getAppTitleAsLPCWSTR();
	ScreenMode getScreenMode();
	Size* getScreenSize();
	Color* getBackBufferColor();


	// Setter
	void setFPS(int _fps);
	void setAppTitle(string _appTitle);
	void setScreenMode(ScreenMode _screenMode);
	void setScreenSize(Size* _screenSize);
	void setBackBufferColor(Color* _backBufferColor);


	// Others
	void save();
	void load();
};