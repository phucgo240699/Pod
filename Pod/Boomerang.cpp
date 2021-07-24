#include "Boomerang.h"
#include "Mario.h"
#include "Boomerang.h"

Boomerang::Boomerang(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY, _id);
	this->originVx = _vx;
	this->originVy = _vy;
}

BoomerangState Boomerang::getState()
{
	return this->state;
}

float Boomerang::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float Boomerang::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float Boomerang::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

float Boomerang::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

Animation* Boomerang::getAnimation()
{
	return this->animation;
}

void Boomerang::setState(BoomerangState _state)
{
	switch (_state)
	{
	case BOOMERANG_STAYING:
		this->setVx(0);
		this->setVy(0);
		break;
	case BOOMERANG_FLYING_LEFT:
		this->countFlyingX = 0;
		this->startFlyingY = this->getY();
		this->setVx(-abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	case BOOMERANG_FLYING_RIGHT:
		this->countFlyingX = 0;
		this->startFlyingY = this->getY();
		this->setVx(abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	case BOOMERANG_FLYING_LEFT_BACK:
		this->setVx(-abs(this->originVx));
		this->setVy(0);
		break;
	case BOOMERANG_FLYING_RIGHT_BACK:
		this->setVx(abs(this->originVx));
		this->setVy(0);
		break;
	default:
		break;
	}

	this->state = _state;
}

void Boomerang::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void Boomerang::Update(float _dt)
{
	Component::Update(_dt);
	if (this->getState() == BoomerangState::BOOMERANG_STAYING) return;
	this->animation->Update(_dt);

	if (this->getState() == BoomerangState::BOOMERANG_FLYING_LEFT) {
		// vx now is < 0
		countFlyingX += (this->getVx() * _dt);
		float moreY = (-1 * (32 - (pow(countFlyingX + 72, 2) / 162)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX < -150) {
			this->setState(BoomerangState::BOOMERANG_FLYING_RIGHT_BACK);
		}
	}
	else if (this->getState() == BoomerangState::BOOMERANG_FLYING_RIGHT){
		// vx now is < 0
		countFlyingX += (this->getVx() * _dt);
		float moreY = (-1 * (32 - (pow(countFlyingX - 72, 2) / 162)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX > 150) {
			this->setState(BoomerangState::BOOMERANG_FLYING_LEFT_BACK);
		}
	}
	else if (this->getState() == BoomerangState::BOOMERANG_FLYING_LEFT_BACK) {
		this->plusXNoRound(this->getVx() * _dt);
	}
	else if (this->getState() == BoomerangState::BOOMERANG_FLYING_RIGHT_BACK) {
		this->plusXNoRound(this->getVx() * _dt);
	}
}

void Boomerang::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == BOOMERANG_STAYING) return;
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}

void Boomerang::hanldeBoomerangBroCollision(BoomerangBro* _boomerangBro, float _dt)
{
	if (_boomerangBro->getState() == BOOMERANG_BRO_BEING_DEAD) return;
	if (this->getState() == BOOMERANG_STAYING) return;

	if (this->getState() == BoomerangState::BOOMERANG_FLYING_LEFT_BACK || this->getState() == BoomerangState::BOOMERANG_FLYING_RIGHT_BACK) {
		tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_boomerangBro, _dt);

		if (get<0>(collisionResult) == true) {
			this->setState(BoomerangState::BOOMERANG_STAYING);
		}
	}
}

void Boomerang::handleMarioCollision(Mario* _mario, float _dt)
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
		|| _mario->getIsFlashMode()) {
		return;
	}

	if (this->getState() == BOOMERANG_STAYING) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true) {
		_mario->setState(MarioState::DIE);
	}
}
