#include "AppConfig.h"

AppConfig::AppConfig()
{
	setting = Setting::getInstance();
	setting->load();
	appController = new AppController();
}

AppConfig::~AppConfig()
{
	delete setting;
	delete appController;
}
