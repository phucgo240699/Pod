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
