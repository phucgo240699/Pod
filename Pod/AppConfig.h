#pragma once
#include"AppController.h"
#include"Man1.h"

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