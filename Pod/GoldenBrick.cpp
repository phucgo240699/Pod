#include "GoldenBrick.h"

GoldenBrick::GoldenBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

GoldenBrick::GoldenBrick(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

GoldenBrickState GoldenBrick::getState()
{
	return this->state;
}

void GoldenBrick::setState(GoldenBrickState _state)
{
	this->state = _state;
}

void GoldenBrick::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->setId(v[4]);
}

void GoldenBrick::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void GoldenBrick::Update(float _dt)
{
	animation->Update(_dt);
}

void GoldenBrick::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	/*D3DXVECTOR3 position = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->getY() - Camera::getInstance()->getY(), 0);
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), &position);*/

	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}
