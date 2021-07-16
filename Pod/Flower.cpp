#include "Flower.h"
#include "Camera.h"
#include "Mario.h"

Flower::Flower(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY, _id);
	this->originVy = _vy;
}

FlowerState Flower::getState()
{
	return this->state;
}

int Flower::getCountDown()
{
	return this->countDown;
}

float Flower::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float Flower::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float Flower::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

float Flower::getBoundsHeight()
{
	return this->animation->getCurrentBoundsWidth();
}

float Flower::getTopAnchor()
{
	return this->topAnchor;
}

float Flower::getBottomAnchor()
{
	return this->bottomAnchor;
}

float Flower::getLeftAnchor()
{
	return this->leftAnchor;
}

float Flower::getRightAnchor()
{
	return this->rightAnchor;
}

bool Flower::getIsHalfSizeMode()
{
	return this->isHalfSizeMode;
}

bool Flower::getIsGreenMode()
{
	return this->isGreenMode;
}

void Flower::setState(FlowerState _state)
{
	if (this->animation == NULL) {
		if (this->getIsHalfSizeMode()) {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFlowerHalfSize());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFlowerHalfSize());
			}
		}
		else {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFlower());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFlower());
			}
		}
	}
	switch (_state)
	{
	case FLOWER_HIDING:
		this->setVy(0);
		this->countDown = 120;
		break;
	case FLOWER_GROWING_UP:
		this->setVy(-abs(this->originVy));
		this->countDown = 80;
		break;
	case FLOWER_DROPPING:
		this->setVy(abs(this->originVy));
		break;
	case FLOWER_STANDING:
		this->setVy(0);
	default:
		break;
	}
	this->state = _state;
}

void Flower::reduceCountDown()
{
	this->countDown -= 1;
}

void Flower::setIsHalfSizeMode(bool _isHalfSizeMode)
{
	this->isHalfSizeMode = _isHalfSizeMode;
}

void Flower::setIsGreenMode(bool _isGreenMode)
{
	this->isGreenMode = _isGreenMode;
}

void Flower::loadInfo(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVy(v[2]);
	this->originVy = v[2];
	this->topAnchor = v[3];
	this->bottomAnchor = v[4];
	this->leftAnchor = v[5];
	this->rightAnchor = v[6];
	this->setIsHalfSizeMode(v[7] == 1);
	this->setIsGreenMode(v[8] == 1);
	this->setId(v[9]);
}

void Flower::Update(float _dt)
{
	if (this->getState() == FLOWER_GROWING_UP && this->getY() + this->getVy() * _dt < topAnchor) {
		this->setY(this->topAnchor);
		this->setState(FlowerState::FLOWER_STANDING);
		return;
	}
	else if (this->getState() == FLOWER_STANDING) {
		if (countDown <= 0) {
			this->setState(FlowerState::FLOWER_DROPPING);
			return;
		}
		this->countDown -= 1;
	}

	else if (this->getState() == FLOWER_DROPPING && this->getY() + this->getVy() * _dt > bottomAnchor) {
		this->setY(this->bottomAnchor);
		this->setState(FlowerState::FLOWER_HIDING);
		return;
	}
	else if (this->getState() == FLOWER_HIDING) {
		if (countDown <= 0) {
			this->setState(FlowerState::FLOWER_GROWING_UP);
			return;
		}
		this->countDown -= 1;
	}

	this->animation->Update(_dt);
	this->plusYNoRound(this->getVy() * _dt);
}

void Flower::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}

void Flower::handleMarioCollision(Mario* _mario, float _dt)
{
	if (this->getState() == FLOWER_HIDING) return;
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_mario->getBounds())) {
		_mario->setState(MarioState::DIE);
	}
}
