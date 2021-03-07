#pragma once
#include "Size.h"
#include "Tool.h"
#include "Color.h"
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
	LPCWSTR appTitle = Tool::getLPCWSTRFrom("Pod");
	Size* screenSize = new Size(480, 640);
	ScreenMode screenMode = window;
	Color* backBufferColor = new Color(black);

public:
	Setting(const Setting&) = delete; // 3. delete copy constructor
	static Setting* getInstance();	  // 4. public function for client code usage

	// Getter
	int getFPS();
	LPCWSTR getAppTitle();
	Size* getScreenSize();
	ScreenMode getScreenMode();
	Color* getBackBufferColor();


	// Setter
	void setFPS(int _fps);
	void setAppTitle(string _appTitle);
	void setAppTitle(LPCWSTR _appTitle);
	void setScreenSize(Size* _screenSize);
	void setScreenMode(ScreenMode _screenMode);
	void setBackBufferColor(Color* _backBufferColor);


	// Others
	void save();
	void load();
};