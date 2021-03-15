#include "AppConfig.h"

AppConfig::AppConfig()
{
	setting = Setting::getInstance();
	setting->load();
}

AppConfig::~AppConfig()
{
	delete setting;
	delete appController;
}
