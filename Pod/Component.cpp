#include "Component.h"

Component::Component(float _x, float _y)
{
	this->position = new D3DXVECTOR3(_x, _y, 0);
}

Component::Component(D3DXVECTOR3* _position)
{
	this->position = _position;
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

void Component::plusX(float _x)
{
	this->position->x += _x;
}

void Component::plusY(float _y)
{
	this->position->y += _y;
}

void Component::Update()
{
}

void Component::Draw()
{
}

void Component::onKeyUp()
{
}

void Component::onKeyDown(KeyType _keyType)
{
}
