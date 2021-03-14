#include "AppConfig.h"

AppConfig::AppConfig()
{
	setting = Setting::getInstance();
	setting->load();
	appController = new AppController(man1);
}
