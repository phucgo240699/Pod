#include "Bomb.h"
#include "Mario.h"

Bomb::Bomb(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY, _id);
	this->originVx = _vx;
	this->originVy = _vy;
}

BombState Bomb::getState()
{
	return this->state;
}

int Bomb::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

int Bomb::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

int Bomb::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

int Bomb::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

void Bomb::setState(BombState _state)
{
	switch (_state)
	{
	case BOMB_DROPPING_LEFT_SIDE:
		this->countDroppingY = 0;
		this->startDroppingX = this->getX();
		this->setVx(-abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	case BOMB_DROPPING_RIGHT_SIDE:
		this->countDroppingY = 0;
		this->startDroppingX = this->getX();
		this->setVx(abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	case BOMB_STAYING:
		this->setVx(0);
		this->setVy(0);
	default:
		break;
	}
	this->state = _state;
}

void Bomb::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void Bomb::Update(float _dt)
{
	Component::Update(_dt);

	if (this->getState() == BOMB_STAYING) return;

	this->animation->Update(_dt);

	if (this->getState() == BOMB_DROPPING_LEFT_SIDE) {
		countDroppingY += (this->getVy() * _dt);
		float moreX = (pow(-countDroppingY + 6, 2) / 9) - 4;
		this->plusYNoRound(this->getVy() * _dt);
		this->setXNoRound(startDroppingX + moreX);

		if (this->countDroppingY >= 12) {
			this->setState(BombState::BOMB_DROPPING_RIGHT_SIDE);
		}
		else if (this->countDroppingY >= 6) {
			this->setVx(abs(this->originVx));
		}
	}
	else if (this->getState() == BOMB_DROPPING_RIGHT_SIDE) {
		countDroppingY += (this->getVy() * _dt);
		float moreX = 4 - (pow(-countDroppingY + 6, 2) / 9);
		this->plusYNoRound(this->getVy() * _dt);
		this->setXNoRound(startDroppingX + moreX);

		if (this->countDroppingY >= 12) {
			this->setState(BombState::BOMB_DROPPING_LEFT_SIDE);
		}
		else if (this->countDroppingY >= 6) {
			this->setVx(-abs(this->originVx));
		}
	}
}

void Bomb::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == BOMB_STAYING) return;

	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}

void Bomb::handleMarioCollision(Mario* _mario, float _dt)
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

	if (this->getState() == BOMB_STAYING) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_mario->getBounds())) { 
		this->setState(BombState::BOMB_STAYING);
		_mario->increaseBombAttached();
	}
}
