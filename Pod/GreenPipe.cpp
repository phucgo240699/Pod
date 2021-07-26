#include "GreenPipe.h"
#include "AnimationBundle.h"

GreenPipe::GreenPipe(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

GreenPipe::GreenPipe(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

bool GreenPipe::getIsBlackMode()
{
	return this->isBlackMode;
}

bool GreenPipe::getIsDownMode()
{
	return this->isDownMode;
}

int GreenPipe::getFloorNumber()
{
	return this->floorNumber;
}

void GreenPipe::setIsBlackMode(bool _isBlackMode)
{
	this->isBlackMode = _isBlackMode;
}

void GreenPipe::setIsDownMode(bool _isDownMode)
{
	this->isDownMode = _isDownMode;
}

void GreenPipe::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void GreenPipe::loadInfo(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);

	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setWidth(stoi(v[2]));
	this->setHeight(stoi(v[3]));
	this->floorNumber = stoi(v[4]);
	this->setId(stoi(v[5]));
	this->setIsBlackMode(stoi(v[6]) == 1);
	this->setIsDownMode(stoi(v[7]) == 1);
}

void GreenPipe::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, animation->getCurrentFrame(), this->getPosition());
}
