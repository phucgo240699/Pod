#include "PButton.h"

PButton::PButton(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY, _id);
}

PButtonState PButton::getState()
{
	return this->state;
}

int PButton::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

int PButton::getHeight()
{
	return this->animation->getCurrentFrameWidth();
}

void PButton::setState(PButtonState _state)
{
	switch (_state)
	{
	case PBUTTON_ON:
		this->animation = new Animation(AnimationBundle::getInstance()->getPButtonOn());
		break;
	case PBUTTON_OFF:
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getPButtonOff());
		break;
	default:
		break;
	}
	this->state = _state;
}

void PButton::Update(float _dt)
{
	Component::Update(_dt);
}

void PButton::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}