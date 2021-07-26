#include "Coin.h"
#include "Mario.h"

Coin::Coin(float _x, float _y, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

CoinState Coin::getState()
{
	return this->state;
}

int Coin::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

int Coin::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

int Coin::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

int Coin::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

void Coin::setState(CoinState _state)
{
	this->state = _state;
}

void Coin::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void Coin::loadInfo(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setId(v[2]);
}

void Coin::Update(float _dt)
{
	Component::Update(_dt);
	this->animation->Update(_dt);
}

void Coin::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}

void Coin::handleMarioCollision(Mario* _mario, float _dt)
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

	if (this->getState() == COIN_BEING_EARNED) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true) {
		this->setState(CoinState::COIN_BEING_EARNED);
		_mario->plusX(get<1>(collisionResult) * this->getVx());
		_mario->plusY(get<1>(collisionResult) * this->getVy());
	}
	else {
		if (this->isCollidingByBounds(_mario->getBounds())) {
			this->setState(CoinState::COIN_BEING_EARNED);
		}
	}
}
