#include "Ground.h"

Ground::Ground(float _x, float _y, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY);
	this->width = _width;
	this->height = _height;
}

Ground::Ground(D3DXVECTOR3* _position, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY) : Component(_position, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_position, _vx, _vy, _limitX, _limitY);
	this->width = _width;
	this->height = _height;
}

Ground::~Ground()
{
	Component::~Component();
	delete& width;
	delete& height;
}

float Ground::getWidth()
{
	return this->width;
}

float Ground::getHeight()
{
	return this->height;
}

RECT* Ground::getBounds()
{
	RECT* r = new RECT();
	r->top = this->getY();
	r->bottom = this->getY() + this->height;
	r->left = this->getX();
	r->right = this->getX() + this->width;
	return r;
}

void Ground::setWidth(float _width)
{
	this->width = _width;
}

void Ground::setHeight(float _height)
{
	this->height = _height;
}

void Ground::load(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);
	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->setVx(v[4]);
	this->setVy(v[5]);
	this->setLimitX(v[6]);
	this->setLimitY(v[7]);
}
