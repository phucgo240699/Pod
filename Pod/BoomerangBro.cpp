#include "BoomerangBro.h"
#include "Mario.h"

BoomerangBro::BoomerangBro(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

void BoomerangBro::loadInfo(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);
	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(v[2]);
	this->setVy(v[3]);
	this->setId(v[4]);
	this->leftAnchor = v[5];
	this->rightAnchor = v[6];
	this->originVx = this->getVx();
	this->originVy = this->getVy();

	this->firstBoomerang = new Boomerang(this->getX(), this->getY(), v[7], v[8], Camera::getInstance()->getLimitX(), Camera::getInstance()->getLimitY(), v[9]);
	this->secondBoomerang = new Boomerang(this->getX(), this->getY(), v[10], v[11], Camera::getInstance()->getLimitX(), Camera::getInstance()->getLimitY(), v[12]);
	this->throwingAnim = new Animation(AnimationBundle::getInstance()->getBoomerangMovingHolding());
}

bool BoomerangBro::getIsStandOnSurface()
{
	return this->isStandOnSurface;
}

BoomerangBroState BoomerangBro::getState()
{
	return this->state;
}

bool BoomerangBro::getIsHolding()
{
	return this->isHolding;
}

bool BoomerangBro::getIsFlip()
{
	return this->isFlip;
}

float BoomerangBro::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float BoomerangBro::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float BoomerangBro::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

float BoomerangBro::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

Boomerang* BoomerangBro::getFirstBoomerang()
{
	return this->firstBoomerang;
}

Boomerang* BoomerangBro::getSecondBoomerang()
{
	return this->secondBoomerang;
}

void BoomerangBro::setState(BoomerangBroState _state)
{
	switch (_state)
	{
	case BOOMERANG_BRO_MOVING_LEFT:
	{
		delete animation;
		if (this->getIsHolding()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBoomerangMovingHolding());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getBoomerangMoving());
		}

		this->setVx(-abs(this->originVx));
		this->setVy(0);
		break;
	}
	case BOOMERANG_BRO_MOVING_RIGHT:
	{
		delete animation;
		if (this->getIsHolding()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBoomerangMovingHolding());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getBoomerangMoving());
		}

		this->setVx(abs(this->originVx));
		this->setVy(0);
		break;
	}
	case BOOMERANG_BRO_POPPING_LEFT:
	{
		this->countMoving = 0;
		this->countFlyingX = 0;
		this->startFlyingY = this->getY();
		this->setVx(-abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	}
	case BOOMERANG_BRO_POPPING_RIGHT:
	{
		this->countMoving = 0;
		this->countFlyingX = 0;
		this->startFlyingY = this->getY();
		this->setVx(abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	}
	case BOOMERANG_BRO_BEING_DEAD:
	{
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getBoomerangDead());
		this->setVx(0);
		this->setVy(3 * abs(this->originVy));
		break;
	}
	default:
		break;
	}
	this->state = _state;
}

void BoomerangBro::setIsHolding(bool _isHoldinng)
{
	this->isHolding = _isHoldinng;
	if (_isHoldinng == true) {
		countDownFinishStartThrow = 4;
	}
}

void BoomerangBro::setIsFlip(bool _isFlip)
{
	this->isFlip = _isFlip;
}

void BoomerangBro::setMarioX(float _value)
{
	this->marioX = _value;
}

void BoomerangBro::Update(float _dt)
{
	Enemy::Update(_dt);
	
	this->animation->Update(_dt);
	--countDownFinishStartThrow;
	if (this->countDownFinishStartThrow <= 0) {
		this->setIsHolding(false);
	}

	if (this->getState() == BOOMERANG_BRO_MOVING_LEFT) {
		if (this->getX() + this->getVx() * _dt < this->leftAnchor) {
			++countMoving;
			if (this->countMoving > totalMoving) {
				this->setState(BoomerangBroState::BOOMERANG_BRO_POPPING_RIGHT);
			}
			else {
				this->setState(BoomerangBroState::BOOMERANG_BRO_MOVING_RIGHT);
			}
		}
		else {
			this->plusXNoRound(this->getVx() * _dt);
		}
	}
	else if (this->getState() == BOOMERANG_BRO_MOVING_RIGHT) {
		if (this->getX() + this->getBoundsWidth() + this->getVx() * _dt > this->rightAnchor) {
			++countMoving;
			if (this->countMoving > totalMoving) {
				this->setState(BoomerangBroState::BOOMERANG_BRO_POPPING_LEFT);
			}
			else {
				this->setState(BoomerangBroState::BOOMERANG_BRO_MOVING_LEFT);
			}
		}
		else {
			this->plusXNoRound(this->getVx() * _dt);
		}
	}
	else if (this->getState() == BOOMERANG_BRO_POPPING_LEFT) {
		// vx now is < 0
		this->countFlyingX += (this->getVx() * _dt);
		float moreY = (-1 * (16 - (pow(countFlyingX + 8, 2) / 4)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX < -8) {
			this->setVy(abs(this->originVy));
		}
	}
	else if (this->getState() == BOOMERANG_BRO_POPPING_RIGHT) {
		// vx now is < 0
		this->countFlyingX += (this->getVx() * _dt);
		float moreY = (-1 * (16 - (pow(countFlyingX - 8, 2) / 4)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX > 8) {
			this->setVy(abs(this->originVy));
		}
	}
	else if (this->getState() == BOOMERANG_BRO_BEING_DEAD) {
		this->plusYNoRound(this->getVy() * _dt);
		return;
	}


	if (this->leftAnchor - 80 <= this->marioX && this->marioX <= this->rightAnchor + 64) {
		if (countDownToThrowBoomerang <= 1540) {
			if (this->firstBoomerang->getState() == BOOMERANG_STAYING && this->secondBoomerang->getState() == BOOMERANG_STAYING) {
				if (this->getIsFlip()) {
					this->firstBoomerang->getAnimation()->setCurrentIndexFrame(2);
					this->firstBoomerang->setX(this->getX() + this->getBoundsWidth());
					this->firstBoomerang->setY(this->getY() - this->firstBoomerang->getHeight());
					this->firstBoomerang->setState(BoomerangState::BOOMERANG_FLYING_LEFT);
				}
				else {
					this->firstBoomerang->getAnimation()->setCurrentIndexFrame(1);
					this->firstBoomerang->setX(this->getX() + this->firstBoomerang->getHeight());
					this->firstBoomerang->setY(this->getY() - this->firstBoomerang->getHeight());
					this->firstBoomerang->setState(BoomerangState::BOOMERANG_FLYING_RIGHT);
				}
				this->setIsHolding(true);
				Grid::getInstance()->add(this->firstBoomerang);
				Grid::getInstance()->updateCellOf(this->firstBoomerang);
			}

		}
		if (countDownToThrowBoomerang <= 1400) {
			if (this->firstBoomerang->getState() != BOOMERANG_STAYING && this->secondBoomerang->getState() == BOOMERANG_STAYING) {
				if (this->getIsFlip()) {
					this->secondBoomerang->getAnimation()->setCurrentIndexFrame(2);
					this->secondBoomerang->setX(this->getX() + this->getBoundsWidth());
					this->secondBoomerang->setY(this->getY() - this->secondBoomerang->getHeight());
					this->secondBoomerang->setState(BoomerangState::BOOMERANG_FLYING_LEFT);
				}
				else {
					this->secondBoomerang->getAnimation()->setCurrentIndexFrame(1);
					this->secondBoomerang->setX(this->getX() + this->secondBoomerang->getHeight());
					this->secondBoomerang->setY(this->getY() - this->secondBoomerang->getHeight());
					this->secondBoomerang->setState(BoomerangState::BOOMERANG_FLYING_RIGHT);
				}
				this->setIsHolding(true);
				Grid::getInstance()->add(this->secondBoomerang);
				Grid::getInstance()->updateCellOf(this->secondBoomerang);

				countDownToThrowBoomerang = 1700;
			}
		}

		--countDownToThrowBoomerang;
	}
}

void BoomerangBro::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getIsHolding()) {
		Drawing::getInstance()->draw(_texture, this->throwingAnim->getCurrentFrame(), this->getPosition(), D3DXVECTOR2(-4, -8), this->getIsFlip());
	}
	else {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), D3DXVECTOR2(-4, -8), this->getIsFlip());
	}


	if (Setting::getInstance()->getDebugMode()) {
		Drawing::getInstance()->drawDebugBox(this->animation->getCurrentBounds(), NULL, this->getPosition());
	}
}

void BoomerangBro::hanldeHardComponentCollision(Component* _component, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_component, _dt);

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];

		if (edge == bottomEdge) {
			if (this->getState() == BoomerangBroState::BOOMERANG_BRO_POPPING_LEFT || this->getState() == BOOMERANG_BRO_DROPPING_LEFT) {
				this->setState(BoomerangBroState::BOOMERANG_BRO_MOVING_LEFT);
				float a = this->getBoundsHeight();
				this->setY(_component->getY() - this->getBoundsHeight());
			}
			else if (this->getState() == BoomerangBroState::BOOMERANG_BRO_POPPING_RIGHT || this->getState() == BOOMERANG_BRO_DROPPING_RIGHT) {
				this->setState(BoomerangBroState::BOOMERANG_BRO_MOVING_RIGHT);
				float a = this->getBoundsHeight();
				this->setY(_component->getY() - this->getBoundsHeight());
			}
		}
	}
}

void BoomerangBro::handleBoomerangCollision(Boomerang* _boomerang, float _dt)
{
	if (this->getState() == BOOMERANG_BRO_BEING_DEAD) return;
	if (_boomerang->getState() == BOOMERANG_STAYING) return;

	if (_boomerang->getState() == BoomerangState::BOOMERANG_FLYING_LEFT_BACK || _boomerang->getState() == BoomerangState::BOOMERANG_FLYING_RIGHT_BACK) {
		tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_boomerang, _dt);

		if (get<0>(collisionResult) == true || this->isCollidingByBounds(_boomerang->getBounds())) {
			_boomerang->setState(BoomerangState::BOOMERANG_STAYING);
		}
	}
}

void BoomerangBro::handleMarioCollision(Mario* _mario, float _dt)
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

	if (this->getState() == BOOMERANG_BRO_BEING_DEAD) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];

		if (edge == topEdge) {
			_mario->setState(MarioState::JUMPING);
			this->setState(BoomerangBroState::BOOMERANG_BRO_BEING_DEAD);
			ScoreBoard::getInstance()->plusPoint(1000);
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(Animation(AnimationBundle::getInstance()->get1000Points()), this->getX(), this->getY())));
		}
		else {
			_mario->setState(MarioState::DIE);
		}
	}
}

void BoomerangBro::handleFireBallCollision(FireBall* _fireBall, float _dt)
{
	if (_fireBall->getState() == BOOMERANG_BRO_BEING_DEAD) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_fireBall, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_fireBall->getBounds())) {
		this->setState(BoomerangBroState::BOOMERANG_BRO_BEING_DEAD);
		ScoreBoard::getInstance()->plusPoint(1000);
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(Animation(AnimationBundle::getInstance()->get1000Points()), this->getX(), this->getY())));
	}
}
