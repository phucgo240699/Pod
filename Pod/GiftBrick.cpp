#include "GiftBrick.h"

//Animation* GiftBrick::getAnimation()
//{
//	return this->animation;
//}

GiftBrick::GiftBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

GiftBrick::GiftBrick(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

void GiftBrick::setAnimation(Animation* _animaiton)
{
	this->animation = new Animation(*_animaiton);
}

void GiftBrick::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(v[2]);
	this->setVy(v[3]);
}

GiftBrickState GiftBrick::getState()
{
	return this->state;
}



void GiftBrick::setState(GiftBrickState _state)
{
	this->state = _state;
}

void GiftBrick::Update(float _dt)
{
	this->animation->Update(_dt);
}

void GiftBrick::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	D3DXVECTOR3 position = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->getY() - Camera::getInstance()->getY(), 0);
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), &position);
}
