#include "SuperLeaf.h"

SuperLeaf::SuperLeaf(float _x, float _y, float _width, float _height, float _vx, float _vy, int _id) : Component(_x, _y, _vx, _vy, 0, 0, _id)
{
	Component::Component(_x, _y, _vx, _vy, 0, 0, _id);
	this->setWidth(_width);
	this->setHeight(_height);
	this->originVx = _vx;
	this->originVy = _vy;
	this->limitPoppingUp = _y - 48;
	
	this->leftX = _x;
	this->rightX = _x + 32;
}

bool SuperLeaf::getIsFlip()
{
	return this->isFlip;
}

SuperLeafState SuperLeaf::getState()
{
	return this->state;
}

void SuperLeaf::setIsFlip(bool _isFlip)
{
	this->isFlip = _isFlip;
}

void SuperLeaf::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void SuperLeaf::setState(SuperLeafState _state)
{
	switch (_state)
	{
	case SUPER_LEAF_POPPING_UP:
		if (animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getSuperLeaf());
		}
		this->setVx(0);
		this->setVy(-abs(originVy));
		break;
	case SUPER_LEAF_DROPPING:
		if (animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getSuperLeaf());
		}
		this->setVx(0);
		this->setVy(abs(originVy));
		this->topY = this->getY();
		break;
	default:
		break;
	}
	this->state = _state;
}

void SuperLeaf::Update(float _dt)
{
	if (this->getState() == SUPER_LEAF_POPPING_UP) {
		if (this->getY() + this->getVy() * _dt < this->limitPoppingUp) {
			this->setY(limitPoppingUp);
			this->setState(SuperLeafState::SUPER_LEAF_DROPPING);
			return;
		}
		this->plusY(this->getVy()* _dt);
	}
	else if (this->getState() == SUPER_LEAF_DROPPING) {
		//float valX = this->getX();
		float valY = this->getY();

		// --->
		if (this->getIsFlip() == false) {
			//++valX;
			//this->setX(valX);
			valY = (pow(this->getX() - leftX - 24, 2) / 36) - 16;
			if (this->getX() != leftX) { // Only convert when not leftX
				valY *= -1; // Must be multiply to -1. Because Oxy in programming and math is different
			}
			this->plusX(1);
		}

		// <---
		else {
			valY = (pow(this->getX() - leftX - 10, 2) / 36) - 16;
			if (this->getX() != rightX) { // Only convert when not rightX
				valY *= -1; // Must be multiply to -1. Because Oxy in programming and math is different
			}
			this->plusX(-1);
		}
		
		this->setY(this->topY + valY);

		if (this->getX() >= this->rightX) {
			this->topY = this->getY();
			this->setIsFlip(true);
		}
		else if (this->getX() <= this->leftX) {
			this->topY = this->getY();
			this->setIsFlip(false);
		}
	}
}

void SuperLeaf::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), this->getIsFlip());
}
