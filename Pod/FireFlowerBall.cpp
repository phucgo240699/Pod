#include "FireFlowerBall.h"
#include "Mario.h"

FireFlowerBall::FireFlowerBall(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY, _id);
	this->originX = _x;
	this->originY = _y;
	this->originVx = _vx;
	this->originVy = _vy;
}

FireFlowerBallState FireFlowerBall::getState()
{
	return this->state;
}

float FireFlowerBall::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float FireFlowerBall::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float FireFlowerBall::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

float FireFlowerBall::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

void FireFlowerBall::setState(FireFlowerBallState _state)
{
	if (this->animation == NULL) {
		this->animation = new Animation(AnimationBundle::getInstance()->getFireFlowerBall());
	}
	switch (_state)
	{
	case FIRE_FLOWER_BALL_FLYING_STAYING:
		this->setVx(0);
		this->setVy(0);
		break;
	case FIRE_FLOWER_BALL_FLYING_UPPER_LEFT:
		this->setVx(-abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	case FIRE_FLOWER_BALL_FLYING_UPPER_RIGHT:
		this->setVx(abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	case FIRE_FLOWER_BALL_FLYING_LOWER_LEFT:
		this->setVx(-abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	case FIRE_FLOWER_BALL_FLYING_LOWER_RIGHT:
		this->setVx(abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	default:
		break;
	}
	this->state = _state;
}

void FireFlowerBall::resetToOriginalPosition()
{
	this->setX(this->originX);
	this->setY(this->originY);
}

//void FireFlowerBall::loadInfo(string line, char seperator)
//{
//	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);
//
//	this->setX(v[0]);
//	this->setY(v[1]);
//	this->setVx(v[2]);
//	this->setVy(v[3]);
//	this->originVx = this->getVx();
//	this->originVy = this->getVy();
//}

void FireFlowerBall::Update(float _dt)
{
	if (this->getState() != FIRE_FLOWER_BALL_FLYING_STAYING) {
		this->animation->Update(_dt);
		this->plusXNoRound(this->getVx() * _dt);
		this->plusYNoRound(this->getVy() * _dt);
	}
}

void FireFlowerBall::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() != FIRE_FLOWER_BALL_FLYING_STAYING) {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
	}
}

void FireFlowerBall::handleMarioCollision(Mario* _mario, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_mario->getBounds())) {
		_mario->setState(MarioState::DIE);
	}
}
