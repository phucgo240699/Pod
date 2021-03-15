#pragma once
#include"AppController.h"

class AppConfig {
public:
	// Properties
	Setting* setting;
	AppController* appController;

	// Init
	AppConfig();

	// De Init
	~AppConfig();
};