#include "Boss.h"
#include "Mario.h"
#include "FireBall.h"
#include "Koopa.h"


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
	r.top = int(this->getY()) - 8;
	r.bottom = r.top + this->getHeight();
	r.left = int(this->getX()) - 4;
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

int Boss::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

int Boss::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

int Boss::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

int Boss::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

Bomb* Boss::getFirstBomb()
{
	return this->firstBomb;
}

Bomb* Boss::getSecondBomb()
{
	return this->secondBomb;
}

Bomb* Boss::getThirdBomb()
{
	return this->thirdBomb;
}

void Boss::setState(BossState _state)
{
	switch (_state)
	{
	case BOSS_MOVING_LEFT:
	{
		//if ((this->getState() != BOSS_MOVING_RIGHT && this->getState() != BOSS_MOVING_RIGHT) || this->animation == NULL) {
			delete animation;
			if (this->getIsFlyingMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getBossMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
			}
		//}

		this->countFlying = 0;
		this->setVx(-abs(this->originVx));
		this->setVy(0);
		break;
	}
	case BOSS_MOVING_RIGHT:
	{
		/*if ((this->getState() != BOSS_MOVING_RIGHT && this->getState() != BOSS_MOVING_RIGHT) || this->animation == NULL) {*/
			delete animation;
			if (this->getIsFlyingMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getBossMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
			}
		//}

		this->countFlying = 0;
		this->setVx(abs(this->originVx));
		this->setVy(0);
		break;
	}
	case BOSS_FLYING_TOP_LEFT:
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
		this->setVy(-3 * abs(this->originVy));
		break;
	}
	case BOSS_FLYING_TOP_RIGHT:
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
		this->setVy(-3 * abs(this->originVy));
		break;
	}
	case BOSS_FLYING_LEFT:
	{
		delete animation;
		if (this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}

		this->countFlyingX = 0;
		this->startFlyingY = this->getY();
		this->countFlying += 1;
		this->setVx(-2 * abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	}
	case BOSS_FLYING_RIGHT:
	{
		delete animation;
		if (this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossFlying());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}

		this->countFlyingX = 0;
		this->startFlyingY = this->getY();
		this->countFlying += 1;
		this->setVx(2 * abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	}
	case BOSS_DROPPING_LEFT:
	{
		delete animation;
		if (this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossDropping());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}

		this->countFlying = 0;
		this->setVx(-abs(this->originVx));
		this->setVy(2 * abs(this->originVy));
		break;
	}
	case BOSS_DROPPING_RIGHT:
	{
		delete animation;
		if (this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getBossDropping());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}

		this->countFlying = 0;
		this->setVx(abs(this->originVx));
		this->setVy(2 * abs(this->originVy));
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
	case BOSS_THROWING_LEFT_AWAT:
	{
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getThrownAwayGoomba());

		this->countDownToDead = 12;
		this->countThrowingX = 0;
		this->startThrowingY = this->getY();
		break;
	}
	case BOSS_THROWING_RIGHT_AWAY:
	{
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getThrownAwayGoomba());

		this->countThrowingX = 0;
		this->startThrowingY = this->getY();
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
	vector<string> v = Tool::splitToVectorStringFrom(line, separator);

	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setVx(stof(v[2]));
	this->setVy(stof(v[3]));
	this->setId(stoi(v[4]));
	this->originVx = this->getVx();
	this->originVy = this->getVy();

	this->firstBomb = new Bomb(this->getX(), this->getY(), stof(v[5]), stof(v[6]), Camera::getInstance()->getLimitX(), Camera::getInstance()->getLimitY(), stoi(v[7]));
	this->secondBomb = new Bomb(this->getX(), this->getY(), stof(v[8]), stof(v[9]), Camera::getInstance()->getLimitX(), Camera::getInstance()->getLimitY(), stoi(v[10]));
	this->thirdBomb = new Bomb(this->getX(), this->getY(), stof(v[11]), stof(v[12]), Camera::getInstance()->getLimitX(), Camera::getInstance()->getLimitY(), stoi(v[13]));

	this->setDefaultPoint(100);
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

		if (this->getIsFlyingMode()) {
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
			/*else {
				if (countDownFromMovingToFlyingUp = 15) {
					if (this->getX() < this->getMarioX()) {
						this->setState(BossState::BOSS_MOVING_RIGHT);
					}
				}
			}*/
			
		}
		else {
			this->plusX(this->getVx() * _dt);
		}
	}
	else if (this->getState() == BOSS_MOVING_RIGHT) {
		if (this->getX() + this->getWidth() + this->getVx() * _dt >= this->getLimitX()) {
			this->setState(BossState::BOSS_MOVING_RIGHT);
		}
		if (this->getIsFlyingMode()) {
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
			/*else {
				if (countDownFromMovingToFlyingUp = 15) {
					if (this->getX() > this->getMarioX()) {
						this->setState(BossState::BOSS_MOVING_LEFT);
					}
				}
			}*/
		}
		else {
			this->plusX(this->getVx() * _dt);
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
		float moreY = -(float(pow(countFlyingX + 15, 2)) / 56 - 4);
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX <= -15) {
			this->setVy(-abs(this->originVy));
		}

		if (this->countFlying > 5) {
			this->setState(BossState::BOSS_DROPPING_LEFT);
		}
		else {
			if (countFlyingX <= -30) {
				if (countFlying == 1) {
					if (this->firstBomb->getState() == BOMB_STAYING) {
						this->firstBomb->setX(this->getX());
						this->firstBomb->setY(this->getY());
						this->firstBomb->setState(BombState::BOMB_DROPPING_RIGHT_SIDE);
						Grid::getInstance()->add(this->firstBomb);
						Grid::getInstance()->updateCellOf(this->firstBomb);
					}
				}
				else if (countFlying == 3) {
					if (this->secondBomb->getState() == BOMB_STAYING) {
						this->secondBomb->setX(this->getX());
						this->secondBomb->setY(this->getY());
						this->secondBomb->setState(BombState::BOMB_DROPPING_RIGHT_SIDE);
						Grid::getInstance()->add(this->secondBomb);
						Grid::getInstance()->updateCellOf(this->secondBomb);
					}
				}
				else if (countFlying == 5) {
					if (this->thirdBomb->getState() == BOMB_STAYING) {
						this->thirdBomb->setX(this->getX());
						this->thirdBomb->setY(this->getY());
						this->thirdBomb->setState(BombState::BOMB_DROPPING_RIGHT_SIDE);
						Grid::getInstance()->add(this->thirdBomb);
						Grid::getInstance()->updateCellOf(this->thirdBomb);
					}
				}
				countFlying++;
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
		float moreY = -(float(pow(countFlyingX - 15, 2)) / 56 - 4);
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX >= 15) {
			this->setVy(-abs(this->originVy));
		}
		if (this->countFlying > 5) {
			this->setState(BossState::BOSS_DROPPING_RIGHT);
		}
		else {
			if (countFlyingX >= 30) {
				if (countFlying == 1) {
					if (this->firstBomb->getState() == BOMB_STAYING) {
						this->firstBomb->setX(this->getX());
						this->firstBomb->setY(this->getY());
						this->firstBomb->setState(BombState::BOMB_DROPPING_RIGHT_SIDE);
						Grid::getInstance()->add(this->firstBomb);
						Grid::getInstance()->updateCellOf(this->firstBomb);
					}
				}
				else if (countFlying == 3) {
					if (this->secondBomb->getState() == BOMB_STAYING) {
						this->secondBomb->setX(this->getX());
						this->secondBomb->setY(this->getY());
						this->secondBomb->setState(BombState::BOMB_DROPPING_RIGHT_SIDE);
						Grid::getInstance()->add(this->secondBomb);
						Grid::getInstance()->updateCellOf(this->secondBomb);
					}
				}
				else if (countFlying == 5) {
					if (this->thirdBomb->getState() == BOMB_STAYING) {
						this->thirdBomb->setX(this->getX());
						this->thirdBomb->setY(this->getY());
						this->thirdBomb->setState(BombState::BOMB_DROPPING_RIGHT_SIDE);
						Grid::getInstance()->add(this->thirdBomb);
						Grid::getInstance()->updateCellOf(this->thirdBomb);
					}
				}
				countFlying++;
				if (this->getX() > this->getMarioX()) {
					this->setState(BossState::BOSS_FLYING_LEFT);
				}
				else {
					this->setState(BossState::BOSS_FLYING_RIGHT);
				}
			}
		}
	}
	else if (this->getState() == BOSS_TRAMPLED) {
		if (this->countDownToDead <= 0) {
			this->setState(BossState::BOSS_DEAD);
		}
		--countDownToDead;
	}
	else if (this->getState() == BOSS_THROWING_LEFT_AWAT) {
		this->plusXNoRound(-2);
		this->setY(this->startThrowingY + (-1 * (16 - (float(pow(countThrowingX + 24, 2)) / 36)))); // -1: Oxy in game vs math
		countThrowingX -= (2);
	}
	else if (this->getState() == BOSS_THROWING_RIGHT_AWAY) {
		this->plusXNoRound(2);
		this->setY(this->startThrowingY + (-1 * (16 - (float(pow(countThrowingX - 24, 2)) / 36)))); // -1: Oxy in game vs math
		countThrowingX += (2);
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
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == BOSS_DROPPING_LEFT || this->getState() == BOSS_DROPPING_RIGHT) {
					if (this->getX() < this->getMarioX()) {
						this->setState(BossState::BOSS_MOVING_RIGHT);
					}
					else {
						this->setState(BossState::BOSS_MOVING_LEFT);
					}
				}

				this->setY(_component->getY() - this->getBoundsHeight());
			}
			else if (edge == leftEdge && this->getIsFlyingMode() == false && this->getY() + this->getBoundsHeight() != _component->getY() && this->getY() != _component->getY() + _component->getHeight()) {
				if (this->getState() == BOSS_MOVING_LEFT) {
					this->setState(BossState::BOSS_MOVING_RIGHT);
				}
				else if (this->getState() == BOSS_DROPPING_LEFT) {
					this->setState(BossState::BOSS_DROPPING_RIGHT);
				}
			}
			else if (edge == rightEdge && this->getIsFlyingMode() == false && this->getY() + this->getBoundsHeight() != _component->getY() && this->getY() != _component->getY() + _component->getHeight()) {
				if (this->getState() == BOSS_MOVING_RIGHT) {
					this->setState(BossState::BOSS_MOVING_LEFT);
				}
				else if (this->getState() == BOSS_DROPPING_RIGHT) {
					this->setState(BossState::BOSS_DROPPING_LEFT);
				}
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

void Boss::handleBlockComponentCollision(Component* _component, float _dt)
{

	if (this->getState() == BOSS_TRAMPLED || this->getState() == BOSS_DEAD) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_component, _dt);
	if (get<0>(collisionResult) == true) {
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == BOSS_DROPPING_LEFT || this->getState() == BOSS_DROPPING_RIGHT) {
					if (this->getX() < this->getMarioX()) {
						this->setState(BossState::BOSS_MOVING_RIGHT);
					}
					else {
						this->setState(BossState::BOSS_MOVING_LEFT);
					}
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

void Boss::handleMarioCollision(Mario* _mario, float _dt)
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

	if (this->getState() == BOSS_THROWING_LEFT_AWAT || this->getState() == BOSS_THROWING_RIGHT_AWAY || this->getState() == BOSS_TRAMPLED || this->getState() == BOSS_DEAD) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];

		if (edge == topEdge) {
			_mario->setState(MarioState::JUMPING);
			
			if (this->getIsFlyingMode()) {
				this->setIsFlyingMode(false);

				if (this->getState() == BOSS_DROPPING_LEFT) {
					this->setState(BossState::BOSS_DROPPING_LEFT);
				}
				else if (this->getState() == BOSS_DROPPING_RIGHT) {
					this->setState(BossState::BOSS_DROPPING_RIGHT);
				}
				else if (this->getState() == BOSS_FLYING_LEFT) {
					this->setState(BossState::BOSS_DROPPING_LEFT);
				}
				else if (this->getState() == BOSS_FLYING_RIGHT) {
					this->setState(BossState::BOSS_DROPPING_RIGHT);
				}
				else if (this->getState() == BOSS_FLYING_TOP_LEFT) {
					this->setState(BossState::BOSS_DROPPING_LEFT);
				}
				else if (this->getState() == BOSS_FLYING_TOP_RIGHT) {
					this->setState(BossState::BOSS_DROPPING_RIGHT);
				}
				else if (this->getState() == BOSS_MOVING_LEFT) {
					this->setState(BossState::BOSS_MOVING_LEFT);
				}
				else if (this->getState() == BOSS_MOVING_RIGHT) {
					this->setState(BossState::BOSS_MOVING_RIGHT);
				}
			}
			else {
				this->setState(BossState::BOSS_TRAMPLED);
				AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint() * this->getPointCoef(), this->getX(), this->getY())));
			}

			// Calculate points
			_mario->increasePointCoef();
			this->setPointCoef(_mario->getPointCoef());
			ScoreBoard::getInstance()->plusPoint(this->getDefaultPoint() * this->getPointCoef());
		}
		else {
			this->plusX(this->getVx() * get<1>(collisionResult));
			_mario->setState(MarioState::DIE);
		}
	}
}

void Boss::handleFireBallCollision(FireBall* _fireBall, float _dt)
{

	if (this->getState() == BOSS_DEAD || this->getState() == BOSS_TRAMPLED || this->getState() == BOSS_THROWING_LEFT_AWAT || this->getState() == BOSS_THROWING_RIGHT_AWAY) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_fireBall, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByFrame(_fireBall->getFrame())) {
		_fireBall->plusX(get<1>(collisionResult) * _fireBall->getVx());
		_fireBall->plusY(get<1>(collisionResult) * _fireBall->getVy());

		this->plusX(get<1>(collisionResult) * this->getVx());
		this->plusX(get<1>(collisionResult) * this->getVx());
		if (_fireBall->getState() == FIREBALL_FLYING_LEFT) {
			this->setState(BossState::BOSS_THROWING_LEFT_AWAT);
		}
		else if (_fireBall->getState() == FIREBALL_FLYING_RIGHT) {
			this->setState(BossState::BOSS_THROWING_RIGHT_AWAY);
		}

		_fireBall->setState(FireBallState::FIREBALL_DISAPPEARED);

		ScoreBoard::getInstance()->plusPoint(this->getDefaultPoint());
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint(), this->getX(), this->getY())));
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), _fireBall->getX(), _fireBall->getY())));
	}
}

void Boss::handleKoopaCollision(Koopa* _koopa, float _dt)
{
	if (_koopa->getState() == KOOPA_THROWN_LEFT_AWAY || _koopa->getState() == KOOPA_THROWN_RIGHT_AWAY) return;

	if (this->getState() == BOSS_THROWING_LEFT_AWAT || this->getState() == BOSS_THROWING_RIGHT_AWAY || this->getState() == BOSS_TRAMPLED || this->getState() == BOSS_DEAD) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_koopa, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (_koopa->getState() == KOOPA_SHRINKAGE_MOVING_LEFT
			|| _koopa->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
			this->setState(BossState::BOSS_THROWING_LEFT_AWAT);

			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(100, this->getX(), this->getY())));
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(this->getX(), this->getY())));
			
		}
		else if (_koopa->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
			|| _koopa->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
			this->setState(BossState::BOSS_THROWING_RIGHT_AWAY);

			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(100, this->getX(), this->getY())));
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(this->getX(), this->getY())));
		}
	}
}
