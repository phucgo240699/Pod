#include "FilePath.h"

FilePath* FilePath::instance;

FilePath* FilePath::getInstance()
{
	if (instance == nullptr) {
		instance = new FilePath();
	}
	return instance;
}
