#include "FireFlower.h"

FireFlower::FireFlower(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY, _id);
	this->originVy = _vy;
}

FireFlowerState FireFlower::getState()
{
	return this->state;
}

int FireFlower::getCountDown()
{
	return this->countDown;
}

bool FireFlower::getIsFlip()
{
	return this->isFlip;
}

float FireFlower::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float FireFlower::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float FireFlower::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

float FireFlower::getBoundsHeight()
{
	return this->animation->getCurrentBoundsWidth();
}

void FireFlower::setState(FireFlowerState _state)
{
	switch (_state)
	{
	case FIRE_FLOWER_STANDING_LOOK_DOWN:
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerStandingLookDown());
		this->setVy(0);
		break;
	case FIRE_FLOWER_STANDING_LOOK_UP:
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerStandingLookUp());
		this->setVy(0);
		break;
	case FIRE_FLOWER_GROWING_UP:
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerGrowingUp());
		this->setVy(-abs(this->originVy));
		this->countDown = 120;
		break;
	case FIRE_FLOWER_DROPPING:
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerDropping());
		this->setVy(abs(this->originVy));
		this->countDown = 120;
		break;
	case FIRE_FLOWER_HIDING:
		this->setVy(0);
		this->countDown = 120;
	default:
		break;
	}
	this->state = _state;
}

void FireFlower::setIsFlip(bool _isFlip)
{
	this->isFlip = _isFlip;
}

void FireFlower::loadInfo(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVy(v[2]);
	this->originVy = v[2];
	this->topAnchor = v[3];
	this->bottomAnchor = this->getY();
	this->setId(v[4]);
}

void FireFlower::Update(float _dt)
{
	if (this->getState() == FIRE_FLOWER_GROWING_UP && this->getY() + this->getVy() * _dt < topAnchor) {
		this->setY(this->topAnchor);
		this->setState(FireFlowerState::FIRE_FLOWER_STANDING_LOOK_DOWN);
		return;
	}
	else if (this->getState() == FIRE_FLOWER_STANDING_LOOK_DOWN) {
		if (countDown <= 0) {
			this->setState(FireFlowerState::FIRE_FLOWER_DROPPING);
			return;
		}
		this->countDown -= 1;
	}
	else if (this->getState() == FIRE_FLOWER_STANDING_LOOK_UP) {
		if (countDown <= 0) {
			this->setState(FireFlowerState::FIRE_FLOWER_GROWING_UP);
			return;
		}
		this->countDown -= 1;
	}

	else if (this->getState() == FIRE_FLOWER_DROPPING && this->getY() + this->getVy() * _dt > bottomAnchor) {
		this->setY(this->bottomAnchor);
		this->setState(FireFlowerState::FIRE_FLOWER_HIDING);
		return;
	}
	else if (this->getState() == FIRE_FLOWER_HIDING) {
		if (countDown <= 0) {
			this->setState(FireFlowerState::FIRE_FLOWER_GROWING_UP);
			return;
		}
		this->countDown -= 1;
	}

	this->animation->Update(_dt);
	this->plusYNoRound(this->getVy() * _dt);
}

void FireFlower::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), this->getIsFlip());
}
