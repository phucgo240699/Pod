#include "Size.h"

Size::Size(int _width, int _height)
{
	if (_width < 0) {
		throw "Error: Width is being less than 0";
		return;
	}
	if (_height < 0) {
		throw "Error: Height is being less than 0";
		return;
	}
	
	this->width = _width;
	this->height = _height;
}

int Size::getWidth()
{
	return this->width;
}

int Size::getHeight()
{
	return this->height;
}

void Size::setWidth(int _width)
{
	if (_width < 0) {
		throw "Error: Width is being less than 0";
		return;
	}

	this->width = _width;
}

void Size::setHeight(int _height)
{
	if (_height < 0) {
		throw "Error: Height is being less than 0";
		return;
	}

	this->height = _height;
}

bool Size::operator==(const Size& size)
{
	if (this->width == size.width && this->height == size.height) {
		return true;
	}
	return false;
}
