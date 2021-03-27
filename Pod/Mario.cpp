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
	this->plusX(vX);
	this->plusY(vY);
}

void Mario::Draw()
{
	Drawing::getInstance()->draw(this->texture, NULL, NULL, this->position, D3DCOLOR_XRGB(255, 255, 255));
}

void Mario::onKeyUp()
{
	vX = 0;
	vY = 0;
}

void Mario::onKeyDown(KeyType _keyType)
{
	switch (_keyType)
	{
	case KeyType::up:
		vY = -1;
		break;
	case KeyType::down:
		vY = 1;
		break;
	case KeyType::left:
		vX = -1;
		break;
	case KeyType::right:
		vX = 1;
		break;
	}
}
