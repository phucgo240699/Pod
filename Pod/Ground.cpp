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