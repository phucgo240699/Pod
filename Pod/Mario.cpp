#include "Mario.h"

Mario::Mario(int _x, int _y, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state = STANDING) : Component(_x, _y)
{
	Component::Component(_x, _y);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->state = _state;
}

Mario::Mario(D3DXVECTOR3* _position, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state = STANDING) : Component(_position)
{
	Component::Component(_position);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->state = _state;
}

Mario::~Mario()
{
	Component::~Component();
	delete& texture;
}

MarioState Mario::getState()
{
	return this->state;
}

void Mario::setState(MarioState _state)
{
	this->state = _state;
}

void Mario::Update()
{
	switch (this->state)
	{
	case MarioState::JUMPING:
		vY = -2;
		break;
	case MarioState::DROPPING:
		vY = 2;
		break;
	case MarioState::WALKING_RIGHT:
		vX = 2;
		break;
	case MarioState::WALKING_LEFT:
		vX = -2;
		break;
	default:
		vX = 0;
		vY = 0;
		break;
	}

	this->setX(this->getX() + vX);
	this->setY(this->getY() + vY);
}

void Mario::Draw()
{
	Drawing::getInstance()->draw(this->texture, NULL, NULL, this->position, D3DCOLOR_XRGB(255, 255, 255));
}
