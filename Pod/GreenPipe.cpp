#include "GreenPipe.h"
#include "AnimationBundle.h"

GreenPipe::GreenPipe(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

GreenPipe::GreenPipe(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

void GreenPipe::setup()
{
	if (this->floorNumber == 2) {
		this->animation = new Animation(AnimationBundle::getInstance()->getGreenPipe2Floor());
	}
	else {
		this->animation = new Animation(AnimationBundle::getInstance()->getGreenPipe3Floor());
	}
}

void GreenPipe::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->floorNumber = v[4];
	this->setId(v[5]);
}

void GreenPipe::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, animation->getCurrentFrame(), this->getPosition());
}
