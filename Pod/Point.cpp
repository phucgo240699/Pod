#include "Point.h"

Point::Point(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
}

int Point::getX()
{
	return this->x;
}

int Point::getY()
{
	return this->y;
}

void Point::setX(int _x)
{
	this->x = _x;
}

void Point::setY(int _y)
{
	this->y = _y;
}

bool Point::operator==(const Point& point)
{
	if (this->x == point.x && this->y == point.y) {
		return true;
	}
	return false;
}
