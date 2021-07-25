#include "Boss.h"

Boss::Boss(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_x, _y, _vx, _vy, _limitX, _limitY)
{
	Enemy::Enemy(_x, _y, _vx, _vy, _limitX, _limitY);
}

bool Boss::getIsStandOnSurface()
{
	return this->isStandOnSurface;
}

BossState Boss::getState()
{
	return this->state;
}

RECT Boss::getFrame()
{
	RECT r = RECT();
	r.top = this->getY() - 8;
	r.bottom = r.top + this->getHeight();
	r.left = this->getX() - 4;
	r.right = r.left + this->getWidth();

	return r;
}

bool Boss::getIsFlyingMode()
{
	return this->isFlyingMode;
}

float Boss::getMarioX()
{
	return this->marioX;
}

float Boss::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float Boss::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float Boss::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

float Boss::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

void Boss::setState(BossState _state)
{
	switch (_state)
	{
	case BOSS_MOVING_LEFT:
	{
		delete animation;
		if (this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}

		this->countFlying = 0;
		this->setVx(-abs(this->originVx));
		this->setVy(0);
		break;
	}
	case BOSS_MOVING_RIGHT:
	{
		delete animation;
		if (this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}

		this->countFlying = 0;
		this->setVx(abs(this->originVx));
		this->setVy(0);
		break;
	}
	case BOSS_FLYING_TOP_LEFT:
	{
		if (this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}

		this->countFlying = 0;
		this->setVx(-abs(this->originVx));
		this->setVy(-3 * abs(this->originVy));
		break;
	}
	case BOSS_FLYING_TOP_RIGHT:
	{
		if (this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}

		this->countFlying = 0;
		this->setVx(abs(this->originVx));
		this->setVy(-3 * abs(this->originVy));
		break;
	}
	case BOSS_FLYING_LEFT:
	{
		if (this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}
		this->countFlyingX = 0;
		this->startFlyingY = this->getY();
		this->countFlying += 1;
		this->setVx(-abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	}
	case BOSS_FLYING_RIGHT:
	{
		if (this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}
		this->countFlyingX = 0;
		this->startFlyingY = this->getY();
		this->countFlying += 1;
		this->setVx(abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	}
	case BOSS_DROPPING_LEFT:
	{
		delete animation;
		if (this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}

		this->countFlying = 0;
		this->setVx(-abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	}
	case BOSS_DROPPING_RIGHT:
	{
		delete animation;
		if (this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}

		this->countFlying = 0;
		this->setVx(abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	}

	case BOSS_TRAMPLED:
	{
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getTrampledGoomba());

		this->countFlying = 0;
		this->setVx(0);
		this->setVy(0);
		break;
	}
	default:
		break;
	}
	this->state = _state;
}

void Boss::setIsFlyingMode(bool _isFlyingMode)
{
	this->isFlyingMode = _isFlyingMode;
}

void Boss::setMarioX(float _marioX)
{
	this->marioX = _marioX;
}

void Boss::loadInfo(string line, char separator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, separator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(v[2]);
	this->setVy(v[3]);
	this->setId(v[4]);
	this->originVx = this->getVx();
	this->originVy = this->getVy();
}

void Boss::Update(float _dt)
{
	Enemy::Update(_dt);

	if (this->getState() == BOSS_DEAD) return;
	
	this->animation->Update(_dt);

	if (this->getIsStandOnSurface()) {
		this->setIsStandOnSurface(false);
	}

	if (this->getState() == BOSS_MOVING_LEFT) {
		if (this->getX() + this->getVx() * _dt <= 0) {
			this->setState(BossState::BOSS_MOVING_RIGHT);
		}
		else {
			this->plusX(this->getVx() * _dt);

			--countDownFromMovingToFlyingUp;
			if (this->countDownFromMovingToFlyingUp <= 0) {
				this->countDownFromMovingToFlyingUp = movingWay;
				if (this->getX() < this->getMarioX()) {
					this->setState(BossState::BOSS_FLYING_TOP_RIGHT);
				}
				else {
					this->setState(BossState::BOSS_FLYING_TOP_LEFT);
				}
			}
			else {
				if (this->getMarioX() > this->getX()) {
					this->setState(BossState::BOSS_MOVING_RIGHT);
				}
			}
		}
	}
	else if (this->getState() == BOSS_MOVING_RIGHT) {
		if (this->getX() + this->getWidth() + this->getVx() * _dt >= this->getLimitX()) {
			this->setState(BossState::BOSS_MOVING_RIGHT);
		}
		else {
			this->plusX(this->getVx() * _dt);

			--countDownFromMovingToFlyingUp;
			if (this->countDownFromMovingToFlyingUp <= 0) {
				this->countDownFromMovingToFlyingUp = movingWay;
				if (this->getX() < this->getMarioX()) {
					this->setState(BossState::BOSS_FLYING_TOP_RIGHT);
				}
				else {
					this->setState(BossState::BOSS_FLYING_TOP_LEFT);
				}
			}
			else {
				if (this->getMarioX() < this->getX()) {
					this->setState(BossState::BOSS_MOVING_RIGHT);
				}
			}
		}
	}
	else if (this->getState() == BOSS_DROPPING_LEFT) {
		if (this->getX() + this->getVx() * _dt <= 0) {
			this->setState(BossState::BOSS_DROPPING_RIGHT);
		}
		else {
			this->plusX(this->getVx() * _dt);
			this->plusY(this->getVy() * _dt);
		}
	}
	else if (this->getState() == BOSS_DROPPING_RIGHT) {
		if (this->getX() + this->getWidth() + this->getVx() * _dt >= this->getLimitX()) {
			this->setState(BossState::BOSS_DROPPING_LEFT);
		}
		else {
			this->plusX(this->getVx() * _dt);
			this->plusY(this->getVy() * _dt);
		}
	}
	else if (this->getState() == BOSS_FLYING_TOP_LEFT) {
		if (this->getX() + this->getVx() * _dt <= 0) {
			this->setState(BossState::BOSS_FLYING_RIGHT);
		}
		else {
			this->plusX(this->getVx() * _dt);
			this->plusY(this->getVy() * _dt);

			if (this->getY() < this->getLimitY() - 200) {
				if (this->getMarioX() > this->getX()) {
					this->setState(BossState::BOSS_FLYING_RIGHT);
				}
				else {
					this->setState(BossState::BOSS_FLYING_LEFT);
				}
			}
		}
	}
	else if (this->getState() == BOSS_FLYING_TOP_RIGHT) {
		if (this->getX() + this->getWidth() + this->getVx() * _dt >= this->getLimitX()) {
			this->setState(BossState::BOSS_FLYING_TOP_LEFT);
		}
		else {
			this->plusX(this->getVx() * _dt);
			this->plusY(this->getVy() * _dt);

			if (this->getY() < this->getLimitY() - 200) {
				if (this->getMarioX() > this->getX()) {
					this->setState(BossState::BOSS_FLYING_RIGHT);
				}
				else {
					this->setState(BossState::BOSS_FLYING_LEFT);
				}
			}
		}
	}
	else if (this->getState() == BOSS_FLYING_LEFT) {
		// vx now is < 0
		this->countFlyingX += (this->getVx() * _dt);
		float moreY = -(pow(countFlyingX + 4, 2) / 4 - 4);
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX <= -4) {
			this->setVy(-abs(this->originVy));
		}

		if (this->countFlying > 4) {
			this->setState(BossState::BOSS_DROPPING_LEFT);
		}
		else {
			if (countFlyingX <= -8) {
				++countFlying;
				if (this->getX() < this->getMarioX()) {
					this->setState(BossState::BOSS_FLYING_RIGHT);
				}
				else {
					this->setState(BossState::BOSS_FLYING_LEFT);
				}
			}
		}
	}
	else if (this->getState() == BOSS_FLYING_RIGHT) {
		// vx now is > 0
		this->countFlyingX += (this->getVx() * _dt);
		float moreY = -(pow(countFlyingX - 4, 2) / 4 - 4);
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX >= 4) {
			this->setVy(-abs(this->originVy));
		}
		if (this->countFlying > 4) {
			this->setState(BossState::BOSS_DROPPING_RIGHT);
		}
		else {
			if (countFlyingX >= 8) {
				++countFlying;
				if (this->getX() > this->getMarioX()) {
					this->setState(BossState::BOSS_FLYING_LEFT);
				}
				else {
					this->setState(BossState::BOSS_FLYING_RIGHT);
				}
			}
		}
	}
}

void Boss::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if(this->getState() == BOSS_DEAD) return;

	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), D3DXVECTOR2(-4, -8));

	if (Setting::getInstance()->getDebugMode()) {
		Drawing::getInstance()->drawDebugBox(this->animation->getCurrentBounds(), NULL, this->getPosition());
	}
}

void Boss::handleHardComponentCollision(Component* _component, float _dt)
{
	if (this->getState() == BOSS_TRAMPLED || this->getState() == BOSS_DEAD) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_component, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == BOSS_DROPPING_LEFT) {
					this->setState(BossState::BOSS_MOVING_LEFT);
				}
				else if (this->getState() == BOSS_DROPPING_RIGHT) {
					this->setState(BossState::BOSS_MOVING_RIGHT);
				}
				this->setY(_component->getY() - this->getBoundsHeight());
			}
		}
	}
	else {
		// if supermushroom walk out of ground's top surface, it will drop
		if (this->getState() == BOSS_MOVING_LEFT || this->getState() == BOSS_MOVING_RIGHT) {
			if (this->getIsStandOnSurface() == false) {
				if ((_component->getX() <= this->getX() + this->getWidth() && this->getX() + this->getWidth() <= _component->getX() + _component->getWidth())
					|| (_component->getX() <= this->getX() && this->getX() <= _component->getX() + _component->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _component->getY()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}
