#include "Component.h"

Component::Component(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY)
{
	this->position = new D3DXVECTOR3(_x, _y, 0);
	this->vx = _vx;
	this->vy = _vy;
	this->limitX = _limitX;
	this->limitY = _limitY;
}

Component::Component(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY)
{
	this->position = _position;
	this->vx = _vx;
	this->vy = _vy;
	this->limitX = _limitX;
	this->limitY = _limitY;
}

Component::~Component()
{
	delete position;
}

D3DXVECTOR3* Component::getPosition()
{
	return this->position;
}

float Component::getX()
{
	return this->position->x;
}

float Component::getY()
{
	return this->position->y;
}

float Component::getVx()
{
	return this->vx;
}

float Component::getVy()
{
	return this->vy;
}

float Component::getLimitX()
{
	return this->limitX;
}

float Component::getLimitY()
{
	return this->limitY;
}

void Component::setPosition(D3DXVECTOR3* _position)
{
	this->position = _position;
}

void Component::setX(float _x)
{
	this->position->x = _x;
}

void Component::setY(float _y)
{
	this->position->y = _y;
}

void Component::setVx(float _vx)
{
	this->vx = _vx;
}

void Component::setVy(float _vy)
{
	this->vy = _vy;
}

void Component::setLimitX(float _limitX)
{
	this->limitX = _limitX;
}

void Component::setLimitY(float _limitY)
{
	this->limitY = _limitY;
}

void Component::plusX(float _x)
{
	this->position->x += _x;
}

void Component::plusY(float _y)
{
	this->position->y += _y;
}

void Component::Update(int _dt)
{
}

void Component::Draw()
{
}

RECT* Component::getBounds()
{
	return nullptr;
}

void Component::onKeyUp()
{
}

void Component::onKeyDown(KeyType _keyType)
{
}
