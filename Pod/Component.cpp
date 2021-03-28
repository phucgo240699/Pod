#include "Component.h"

Component::Component(int _x, int _y)
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

int Component::getX()
{
	return this->position->x;
}

int Component::getY()
{
	return this->position->y;
}

void Component::setPosition(D3DXVECTOR3* _position)
{
	this->position = _position;
}

void Component::setX(int _x)
{
	this->position->x = _x;
}

void Component::setY(int _y)
{
	this->position->y = _y;
}

void Component::plusX(int _x)
{
	this->position->x += _x;
}

void Component::plusY(int _y)
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
