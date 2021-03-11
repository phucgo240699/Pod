#include "Rect.h"


// Init
Rect::Rect(Point* _location, Size* _size) {
	this->location = _location;
	this->size = _size;
}

Rect::Rect(int _x, int _y, int _width, int _height) {
	this->location = new Point(_x, _y);
	this->size = new Size(_width, _height);
}

// De-Init
Rect::~Rect()
{
	delete size;
	delete location;
}

// Getter
Point* Rect::getLocation()
{
	return this->location;
}

Size* Rect::getSize()
{
	return this->size;
}

// Setter
void Rect::setLocation(Point* _location)
{
	this->location = _location;
}

void Rect::setSize(Size* _size)
{
	this->size = _size;
}


// Anchors
int Rect::getTopAnchor()
{
	return this->location->getY();
}

int Rect::getBottomAnchor()
{
	return this->location->getY() + this->size->getHeight();
}

int Rect::getLeftAnchor()
{
	return this->location->getX();
}

int Rect::getRightAnchor()
{
	return this->location->getX() + this->size->getWidth();
}


// Detection
bool Rect::isIntersect(Rect anotherRect)
{
	// Top-Left
	if (anotherRect.getLeftAnchor() <= this->getLeftAnchor()
		&& this->getLeftAnchor() <= anotherRect.getRightAnchor()
		&& anotherRect.getTopAnchor() <= this->getTopAnchor()
		&& this->getTopAnchor() <= anotherRect.getBottomAnchor())
	{
		return true;
	}

	// Top-Right
	else if (anotherRect.getLeftAnchor() <= this->getRightAnchor()
		&& this->getRightAnchor() <= anotherRect.getRightAnchor()
		&& anotherRect.getTopAnchor() <= this->getTopAnchor()
		&& this->getTopAnchor() <= anotherRect.getBottomAnchor())
	{
		return true;
	}

	// Bottom-Left
	else if (anotherRect.getLeftAnchor() <= this->getLeftAnchor()
		&& this->getLeftAnchor() <= anotherRect.getRightAnchor()
		&& anotherRect.getTopAnchor() <= this->getBottomAnchor()
		&& this->getBottomAnchor() <= anotherRect.getBottomAnchor())
	{
		return true;
	}

	// Bottom-Right
	else if (anotherRect.getLeftAnchor() <= this->getRightAnchor()
		&& this->getRightAnchor() <= anotherRect.getRightAnchor()
		&& anotherRect.getTopAnchor() <= this->getBottomAnchor()
		&& this->getBottomAnchor() <= anotherRect.getBottomAnchor())
	{
		return true;
	}

	return false;
}

bool Rect::isContain(Rect anotherRect)
{
	if (anotherRect.getTopAnchor() >= this->getTopAnchor()
		&& anotherRect.getBottomAnchor() <= this->getBottomAnchor()
		&& anotherRect.getLeftAnchor() >= this->getLeftAnchor()
		&& anotherRect.getRightAnchor() <= this->getRightAnchor())
	{
		return true;
	}

	return false;
}

RECT Rect::toRECTForD3D()
{
	RECT rect;
	rect.top = this->getTopAnchor();
	rect.bottom = this->getBottomAnchor();
	rect.left = this->getLeftAnchor();
	rect.right = this->getRightAnchor();
	return rect;
}

RECT* Rect::toPointerRECTForD3D()
{
	RECT* rect = new RECT();
	rect->top = this->getTopAnchor();
	rect->bottom = this->getBottomAnchor();
	rect->left = this->getLeftAnchor();
	rect->right = this->getRightAnchor();
	return rect;
}
