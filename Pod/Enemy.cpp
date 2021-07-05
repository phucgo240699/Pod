#include "Enemy.h"

Enemy::Enemy(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY);
}

Enemy::Enemy(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_position, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_position, _vx, _vy, _limitX, _limitY);
}

int Enemy::getPointCoef()
{
	return this->pointCoef;
}

int Enemy::getDefaultPoint()
{
	return this->defaultPoint;
}

void Enemy::setIsStandOnSurface(bool _isStandOnSurface)
{
	this->isStandOnSurface = _isStandOnSurface;
}

void Enemy::setPointCoef(int _pointCoef)
{
	this->pointCoef = _pointCoef;
}

void Enemy::Update(float _dt)
{
	Component::Update(_dt);
}
