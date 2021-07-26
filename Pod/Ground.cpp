#include "Ground.h"

Ground::Ground(float _x, float _y, int _width, int _height, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY);
	this->width = _width;
	this->height = _height;
}

Ground::Ground(D3DXVECTOR3 _position, int _width, int _height, float _vx, float _vy, float _limitX, float _limitY) : Component(_position, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_position, _vx, _vy, _limitX, _limitY);
	this->width = _width;
	this->height = _height;
}

void Ground::load(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);

	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setWidth(stoi(v[2]));
	this->setHeight(stoi(v[3]));
	this->setId(stoi(v[4]));
}
