#pragma once
#include"AppController.h"
#include"Man1.h"

class AppConfig {
public:
	AppConfig();
	Setting* setting;
	ViewController* man1 = new Man1;
	AppController* appController;
};