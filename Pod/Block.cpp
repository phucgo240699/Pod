#include "Block.h"

Block::Block(float _x, float _y, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

Block::Block(D3DXVECTOR3 _position, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

void Block::load(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);

	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setWidth(stoi(v[2]));
	this->setHeight(stoi(v[3]));
	this->setId(stoi(v[4]));
}
