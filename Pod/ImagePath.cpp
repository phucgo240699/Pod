#include "ImagePath.h"
ImagePath* ImagePath::instance;

ImagePath* ImagePath::getInstance()
{
	if (instance == nullptr) {
		instance = new ImagePath();
	}
	return instance;
}
