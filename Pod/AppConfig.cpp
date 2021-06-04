#include "AppConfig.h"

AppConfig::AppConfig()
{
	setting = Setting::getInstance();
	appController = new AppController();
	setting->load();
}

AppConfig::~AppConfig()
{
	delete setting;
	delete appController;
}
