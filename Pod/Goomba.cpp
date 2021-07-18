#include "Goomba.h"
#include "Mario.h"

Goomba::Goomba(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

Goomba::Goomba(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_position, _vx, _vy, _limitX, _limitY)
{
}

void Goomba::loadInfo(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->setVx(v[4]);
	this->setVy(v[5]);
	this->setId(v[7]);

	this->defaultPoint = v[6];
	this->originVx = abs(this->getVx());
	this->originVy = abs(this->getVy());
}

GoombaState Goomba::getState()
{
	return this->state;
}

bool Goomba::getIsStandOnSurface()
{
	return this->isStandOnSurface;
}

void Goomba::setState(GoombaState _state)
{
	switch (_state)
	{
	case GOOMBA_STANDING:
	{
		if (this->animation == NULL) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
			this->setVx(0);
			this->setVy(0);
		}
		break;
	}

	case GOOMBA_MOVING_LEFT:
	{
		if (this->animation == NULL) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		this->setVx(-originVx);
		this->setVy(0);
		break;
	}

	case GOOMBA_MOVING_RIGHT:
	{
		if (this->animation == NULL) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		this->setVx(originVx);
		this->setVy(0);
		break;
	}

	case GOOMBA_DROPPING_LEFT:
	{
		if (this->animation == NULL) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		this->setVx(-originVx);
		this->setVy(originVy);
		break;
	}

	case GOOMBA_DROPPING_RIGHT:
	{
		if (this->animation == NULL) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		this->setVx(originVx);
		this->setVy(originVy);
		break;
	}

	case TRAMPLED_GOOMBA:
	{
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getTrampledGoomba());
		this->setVx(0);
		break;
	}

	case THROWN_LEFT_AWAY_GOOMBA:
	{
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getThrownAwayGoomba());
		this->setVx(-originVx);
		//this->setVy(-1.2 * originVy);
		this->setVy(0);
		this->thrownX = 0;
		this->startThrownY = this->getY();
		break;
	}

	case THROWN_RIGHT_AWAY_GOOMBA:
	{
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getThrownAwayGoomba());
		this->setVx(originVx);
		//this->setVy(-1.2 * originVy);
		this->setVy(0);
		this->thrownX = 0;
		this->startThrownY = this->getY();
		break;
	}

	case DEAD_GOOMBA:
	{
		if (this->getState() == TRAMPLED_GOOMBA) {
			delete animation;
			this->setVx(0);
			this->setVy(0);
		}
		break;
	}
	default:
		break;
	}
	this->state = _state;
}

void Goomba::convertMovingState()
{
	if (this->getState() == GOOMBA_MOVING_LEFT) {
		this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
	}
	else if (this->getState() == GOOMBA_MOVING_RIGHT) {
		this->setState(GoombaState::GOOMBA_MOVING_LEFT);
	}
	else if (this->getState() == GOOMBA_DROPPING_LEFT) {
		this->setState(GoombaState::GOOMBA_DROPPING_RIGHT);
	}
	else if (this->getState() == GOOMBA_DROPPING_RIGHT) {
		this->setState(GoombaState::GOOMBA_DROPPING_LEFT);
	}
}

void Goomba::Update(float _dt)
{
	Enemy::Update(_dt);
	if (this->getState() == DEAD_GOOMBA || this->getState() == GOOMBA_STANDING) return;

	if (this->getIsStandOnSurface() == true) {
		this->setIsStandOnSurface(false);
	}
	
	if (this->getState() == GOOMBA_MOVING_LEFT || this->getState() == GOOMBA_MOVING_RIGHT) {
		if (this->getX() + this->getVx() * _dt >= 0
		&& this->getX() + this->getWidth() + this->getVx() * _dt <= Camera::getInstance()->getLimitX()) {
 			this->plusXNoRound(this->getVx() * _dt);
		}
	}
	else if (this->getState() == GOOMBA_DROPPING_LEFT || this->getState() == GOOMBA_DROPPING_RIGHT) {
		if (this->getX() + this->getVx() * _dt >= 0
			&& this->getX() + this->getWidth() + this->getVx() * _dt <= Camera::getInstance()->getLimitX()) {
			this->plusXNoRound(this->getVx() * _dt);
		}
		this->plusYNoRound(this->getVy() * _dt);
	}
	else if (this->getState() == TRAMPLED_GOOMBA) {
		if (countDownToDead == 0 && alreadyPlayPointCD == false) {
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint() * this->getPointCoef(), this->getX(), this->getY())));
			alreadyPlayPointCD = true;
			countDownToDead = 12;
		}
		else if (countDownToDead <= 0 && alreadyPlayPointCD) {
			this->setState(GoombaState::DEAD_GOOMBA);
			alreadyPlayPointCD = false;
			countDownToDead = 0;
		}

		--countDownToDead;

		return;
	}
	else if (this->getState() == THROWN_LEFT_AWAY_GOOMBA) {
		this->plusXNoRound(-2);
		this->setY(this->startThrownY + (-1 * (16 - (pow(thrownX + 24, 2) / 36)))); // -1: Oxy in game vs math
		thrownX -= (2);
	}
	else if (this->getState() == THROWN_RIGHT_AWAY_GOOMBA) {
		this->plusXNoRound(2);
		this->setY(this->startThrownY + (-1 * (16 - (pow(thrownX - 24, 2) / 36)))); // -1: Oxy in game vs math
		thrownX += (2);
	}
	this->animation->Update(_dt);
}

void Goomba::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == DEAD_GOOMBA) return;
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}

void Goomba::handleHardComponentCollision(Component* _component, float _dt)
{
	if (this->getState() == TRAMPLED_GOOMBA
		|| this->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| this->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| this->getState() == DEAD_GOOMBA) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_component, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == leftEdge) {
				if (this->getState() == GOOMBA_MOVING_LEFT) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
				}
				else if (this->getState() == GOOMBA_DROPPING_LEFT) {
					this->setState(GoombaState::GOOMBA_DROPPING_RIGHT);
				}
			}
			else if (edge == rightEdge) {
				if (this->getState() == GOOMBA_MOVING_RIGHT) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
				}
				else if (this->getState() == GOOMBA_DROPPING_RIGHT) {
					this->setState(GoombaState::GOOMBA_DROPPING_LEFT);
				}
			}
			else if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == GOOMBA_DROPPING_LEFT) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
					this->setY(_component->getY() - this->getHeight());
				}
				else if (this->getState() == GOOMBA_DROPPING_RIGHT) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
					this->setY(_component->getY() - this->getHeight());
				}
			}
		}
	}
	else {
		// if supermushroom walk out of ground's top surface, it will drop
		if (this->getState() == GOOMBA_MOVING_LEFT || this->getState() == GOOMBA_MOVING_RIGHT) {
			if (this->getIsStandOnSurface() == false) {
				if ((_component->getX() <= this->getX() + this->getWidth() && this->getX() + this->getWidth() <= _component->getX() + _component->getWidth())
					|| (_component->getX() <= this->getX() && this->getX() <= _component->getX() + _component->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getHeight() == _component->getY()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Goomba::handleBlockCollision(Component* _block, float _dt)
{
	if (this->getState() == TRAMPLED_GOOMBA
		|| this->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| this->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| this->getState() == DEAD_GOOMBA) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_block, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == SUPER_MUSHROOM_DROPPING_LEFT) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
					this->setY(_block->getY() - this->getHeight());
				}
				else if (this->getState() == SUPER_MUSHROOM_DROPPING_RIGHT) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
					this->setY(_block->getY() - this->getHeight());
				}
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_block->getX() <= this->getX() + this->getWidth() && this->getX() + this->getWidth() <= _block->getX() + _block->getWidth())
					|| (_block->getX() <= this->getX() && this->getX() <= _block->getX() + _block->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getHeight() == _block->getY()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Goomba::handleKoopaCollision(Koopa* _koopa, float _dt)
{
	if (_koopa->getState() == KOOPA_THROWN_LEFT_AWAY || _koopa->getState() == KOOPA_THROWN_RIGHT_AWAY) return;

	if (this->getState() == TRAMPLED_GOOMBA
		|| this->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| this->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| this->getState() == DEAD_GOOMBA) {
		return;
	}
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_koopa, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == leftEdge || edge == rightEdge) {
			if (_koopa->getState() == KOOPA_MOVING_LEFT
				|| _koopa->getState() == KOOPA_MOVING_RIGHT
				|| _koopa->getState() == KOOPA_DROPPING_LEFT
				|| _koopa->getState() == KOOPA_DROPPING_RIGHT) {
				_koopa->plusX(_koopa->getVx() * get<1>(collisionResult));
				_koopa->plusY(_koopa->getVy() * get<1>(collisionResult));
				_koopa->convertMovingState();

				this->plusX(this->getVx() * get<1>(collisionResult));
				this->plusY(this->getVy() * get<1>(collisionResult));
				this->convertMovingState();
			}
		}
		else {
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint() * this->getPointCoef(), this->getX(), this->getY())));
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(this->getX(), this->getY())));
			if (_koopa->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT
				|| _koopa->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
				this->setState(GoombaState::THROWN_LEFT_AWAY_GOOMBA);
			}
			else if (_koopa->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
				|| _koopa->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				this->setState(GoombaState::THROWN_RIGHT_AWAY_GOOMBA);
			}
		}
	}
}

void Goomba::handleMarioCollision(Mario* _mario, float _dt)
{
	if (_mario->getState() == DIE
		|| _mario->getState() == DIE_JUMPING
		|| _mario->getState() == DIE_DROPPING
		|| _mario->getState() == SCALING_UP
		|| _mario->getState() == SCALING_DOWN
		|| _mario->getState() == TRANSFERING_TO_FLY
		|| _mario->getIsFlashMode()) {
		return;
	}

	if (this->getState() == TRAMPLED_GOOMBA
		|| this->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| this->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| this->getState() == DEAD_GOOMBA) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->plusY(2 * get<1>(collisionResult) * this->getVy());
				if (_mario->getIsSuperMode() == false) {
					this->setState(GoombaState::GOOMBA_STANDING);
				}
				_mario->setState(MarioState::DIE);
				this->plusY(get<1>(collisionResult) * this->getVy());
			}
			else if (edge == leftEdge) {
				this->plusX(2 * get<1>(collisionResult) * this->getVx());
				if (_mario->getIsSuperMode() == false) {
					this->setState(GoombaState::GOOMBA_STANDING);
				}
				_mario->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * this->getVx());
			}
			else if (edge == rightEdge) {
				this->plusX(2 * get<1>(collisionResult) * this->getVx());
				if (_mario->getIsSuperMode() == false) {
					this->setState(GoombaState::GOOMBA_STANDING);
				}
				_mario->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * this->getVx());
			}
			else if (edge == topEdge && _mario->getState() == DROPPING) {
				_mario->setState(MarioState::JUMPING);
				_mario->plusY(get<1>(collisionResult) * _mario->getVy() + this->getHeight() / 4);
				this->setState(GoombaState::TRAMPLED_GOOMBA);

				// Calculate points
				_mario->increasePointCoef();
				this->setPointCoef(this->getPointCoef());
				ScoreBoard::getInstance()->plusPoint(this->getDefaultPoint() * this->getPointCoef());
			}
		}
	}
	else if (this->isCollidingByBounds(_mario->getBounds()) && _mario->getState() != DROPPING) {
		this->plusX(2 * get<1>(collisionResult) * this->getVx());
		if (_mario->getIsSuperMode() == false) {
			this->setState(GoombaState::GOOMBA_STANDING);
		}
		_mario->plusX(get<1>(collisionResult) * _mario->getVx());
		_mario->setState(MarioState::DIE);
	}
}

void Goomba::handleFireBallCollision(FireBall* _fireBall, float _dt)
{
	if (this->getState() == TRAMPLED_GOOMBA
		|| this->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| this->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| this->getState() == DEAD_GOOMBA) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_fireBall, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_fireBall->getBounds())) {
		_fireBall->plusX(get<1>(collisionResult) * _fireBall->getVx());
		_fireBall->plusY(get<1>(collisionResult) * _fireBall->getVy());

		this->plusX(get<1>(collisionResult) * this->getVx());
		this->plusX(get<1>(collisionResult) * this->getVx());

		if (_fireBall->getState() == FIREBALL_FLYING_LEFT) {
			this->setState(THROWN_LEFT_AWAY_GOOMBA);
		}
		else if (_fireBall->getState() == FIREBALL_FLYING_RIGHT) {
			this->setState(THROWN_RIGHT_AWAY_GOOMBA);
		}

		_fireBall->setState(FireBallState::FIREBALL_DISAPPEARED);
		ScoreBoard::getInstance()->plusPoint(this->getDefaultPoint());
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint(), this->getX(), this->getY())));
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), _fireBall->getX(), _fireBall->getY())));
	}
}