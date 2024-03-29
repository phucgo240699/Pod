#include "SuperLeaf.h"
#include "Mario.h"

SuperLeaf::SuperLeaf(float _x, float _y, int _width, int _height, float _vx, float _vy, int _id) : Component(_x, _y, _vx, _vy, 0, 0, _id)
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

int SuperLeaf::getDefaultPoints()
{
	return this->defaultPoints;
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
		/*if (animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getSuperLeaf());
		}*/
		this->setVx(0);
		this->setVy(-2 * abs(originVy));
		break;
	case SUPER_LEAF_DROPPING:
		/*if (animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getSuperLeaf());
		}*/
		this->setVx(0);
		this->setVy(abs(originVy));
		this->topY = this->getY();
		break;
	case SUPER_LEAF_BEING_EARNED:
		this->pointAnimation = new Animation(AnimationBundle::getInstance()->get1000Points());
		this->pointPosition = D3DXVECTOR3(this->getX(), this->getY(), 0);
		this->endPointJumpUpY = this->getY() - 36;
		break;
	default:
		break;
	}
	this->state = _state;
}

void SuperLeaf::setDefaultPoints(int _defaultPoints)
{
	this->defaultPoints = _defaultPoints;
}

void SuperLeaf::Update(float _dt)
{
	Component::Update(_dt);

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
			valY = (float(pow(this->getX() - leftX - 24, 2)) / 36) - 16;
			if (this->getX() != leftX) { // Only convert when not leftX
				valY *= -1; // Must be multiply to -1. Because Oxy in programming and math is different
			}
			this->plusX(1);
		}

		// <---
		else {
			valY = (float(pow(this->getX() - leftX - 10, 2)) / 36) - 16;
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
	else if (this->getState() == SUPER_LEAF_BEING_EARNED) {
		if (this->pointPosition.y <= this->endPointJumpUpY) {
			this->setState(SuperLeafState::SUPER_LEAF_DISAPPEARED);
		}

		this->pointPosition.y -= 2;
	}
}

void SuperLeaf::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == SUPER_LEAF_DISAPPEARED) return;

	if (this->getState() == SUPER_LEAF_BEING_EARNED) {
		Drawing::getInstance()->draw(_texture, this->pointAnimation->getCurrentFrame(), this->pointPosition);
		return;
	}

	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), this->getIsFlip());
}

void SuperLeaf::handleMarioCollision(Mario* _mario, float _dt)
{
	if (_mario->getState() == DIE
		|| _mario->getState() == DIE_JUMPING
		|| _mario->getState() == DIE_DROPPING
		|| _mario->getState() == SCALING_UP
		|| _mario->getState() == SCALING_DOWN
		|| _mario->getState() == TRANSFERING_TO_FLY
		|| _mario->getState() == DROPPING_DOWN_PIPE
		|| _mario->getState() == POPPING_UP_PIPE
		|| _mario->getState() == JUMPING_UP_TO_CLOUND
		|| _mario->getState() == DROPPING_DOWN_WIN
		|| _mario->getState() == MOVING_RIGHT_WIN
		|| _mario->getIsFlashMode()
		|| this->getState() == SUPER_LEAF_DISAPPEARED
		|| this->getState() == SUPER_LEAF_BEING_EARNED) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true) {
		//int xPoint = this->getX();
		//int yPoint = this->getY();
		//AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoints(), this->getX(), this->getY())));
		ScoreBoard::getInstance()->plusPoint(1000);

		this->plusX(this->getVx() * get<1>(collisionResult));
		this->plusY(this->getVy() * get<1>(collisionResult));
		this->setState(SuperLeafState::SUPER_LEAF_BEING_EARNED);
		_mario->plusX(_mario->getVx() * get<1>(collisionResult));
		_mario->plusY(_mario->getVy() * get<1>(collisionResult));

		if (_mario->getIsFlyingMode() == false && _mario->getIsSuperMode()) {
			_mario->setState(MarioState::TRANSFERING_TO_FLY);
		}
		else if (_mario->getIsFlyingMode() == false && _mario->getIsSuperMode() == false) {
			_mario->setState(MarioState::SCALING_UP);
		}
	}
	else if (this->isCollidingByBounds(_mario->getBounds())) {
		//int xPoint = this->getX();
		//int yPoint = this->getY();
		//AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoints(), this->getX(), this->getY())));
		ScoreBoard::getInstance()->plusPoint(1000);

		this->setState(SuperLeafState::SUPER_LEAF_BEING_EARNED);

		if (_mario->getIsFlyingMode() == false && _mario->getIsSuperMode()) {
			_mario->setState(MarioState::TRANSFERING_TO_FLY);
		}
		else if (_mario->getIsFlyingMode() == false && _mario->getIsSuperMode() == false) {
			_mario->setState(MarioState::SCALING_UP);
		}
	}
}