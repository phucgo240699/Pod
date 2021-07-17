#include "FireBall.h"
#include "Mario.h"

FireBall::FireBall(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY, _id);
	this->originX = _x;
	this->originY = _y;
	this->originVx = _vx;
}

FireBallState FireBall::getState()
{
	return this->state;
}

float FireBall::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float FireBall::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float FireBall::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

float FireBall::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

bool FireBall::getIsOutOfGrid()
{
	return this->isOutOfGrid;
}

void FireBall::setState(FireBallState _state)
{
	switch (_state)
	{
	case FIREBALL_STAYING:
		this->setVx(0);
		break;
	case FIREBALL_FLYING_LEFT:
		this->setVx(-abs(this->originVx));
		break;
	case FIREBALL_FLYING_RIGHT:
		this->setVx(abs(this->originVx));
		break;
	default:
		break;
	}
	this->state = _state;
}

void FireBall::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void FireBall::resetToOriginalPosition()
{
	this->setX(this->originX);
	this->setY(this->originY);
}

void FireBall::setIsOutOfGrid(bool _isOutOfGrid)
{
	this->isOutOfGrid = _isOutOfGrid;
}

void FireBall::Update(float _dt)
{
	if (this->getState() != FIREBALL_STAYING) {
		this->plusX(this->getVx() * _dt);
	}
}

void FireBall::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() != FIREBALL_STAYING) {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
	}
}

void FireBall::handleMarioCollision(Mario* _mario, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_mario->getBounds())) {
		this->plusX(get<1>(collisionResult) * this->getVx());
		this->plusY(get<1>(collisionResult) * this->getVy());
		_mario->setState(MarioState::DIE);
	}
}
