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
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);

	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setWidth(stoi(v[2]));
	this->setHeight(stoi(v[3]));
	this->setVx(stof(v[4]));
	this->setVy(stof(v[5]));
	this->setId(stoi(v[7]));

	this->defaultPoint = stoi(v[6]);
	this->originVx = abs(this->getVx());
	this->originVy = abs(this->getVy());

	this->setIsFlyingMode(stoi(v[8]) == 1);
	isUseRedSkin = this->getIsFlyingMode();
}

GoombaState Goomba::getState()
{
	return this->state;
}

bool Goomba::getIsStandOnSurface()
{
	return this->isStandOnSurface;
}

bool Goomba::getIsFlyingMode()
{
	return this->isFlyingMode;
}

float Goomba::getMarioX()
{
	return this->marioX;
}

int Goomba::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

int Goomba::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

int Goomba::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

int Goomba::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

//float Goomba::getStoredVy()
//{
//	return this->storedVy;
//}

float Goomba::getOriginVx()
{
	return this->originVx;
}

float Goomba::getOriginVy()
{
	return this->originVy;
}

RECT Goomba::getFrame()
{
	RECT r = RECT();
	r.top = int(this->getY()) - 8;
	r.bottom = r.top + this->getHeight();
	r.left = int(this->getX()) - 4;
	r.right = r.left + this->getWidth();

	return r;
}

void Goomba::setState(GoombaState _state)
{
	switch (_state)
	{
	case GOOMBA_STANDING:
	{
		delete animation;
		if (this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedFlying());
		}
		else if (this->isUseRedSkin) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedMoving());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		
		this->setVx(0);
		this->setVy(0);
		countPopping = 0;
		break;
	}

	case GOOMBA_MOVING_LEFT:
	{
		//if (this->getIsFlyingMode() || this->animation == NULL) {
			delete animation;
			if (this->getIsFlyingMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedFlying());
			}
			else if (this->isUseRedSkin) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
			}
		//}

		//countPopping = 0;
		this->setVx(-getOriginVx());
		this->setVy(0);
		break;
	}

	case GOOMBA_MOVING_RIGHT:
	{
		//if (this->getIsFlyingMode() || this->animation == NULL) {
			delete animation;
			if (this->getIsFlyingMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedFlying());
			}
			else if (this->isUseRedSkin) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
			}
		//}

		//countPopping = 0;
		this->setVx(getOriginVx());
		this->setVy(0);
		break;
	}

	case GOOMBA_DROPPING_LEFT:
	{
		//if (this->getIsFlyingMode() || this->animation == NULL) {
			delete animation;
			if (this->getIsFlyingMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedFlying());
			}
			else if (this->isUseRedSkin) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
			}
		//}
		this->setVx(-getOriginVx());
		this->setVy(getOriginVy());
		break;
	}

	case GOOMBA_DROPPING_RIGHT:
	{
		//if (this->getIsFlyingMode() || this->animation == NULL) {
			delete animation;
			if (this->getIsFlyingMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedFlying());
			}
			else if (this->isUseRedSkin) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
			}
		//}
		this->setVx(getOriginVx());
		this->setVy(getOriginVy());
		break;
	}

	case GOOMBA_POPPING_LEFT:
	{
		//if (animation == NULL) {
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedFlying());
		//}

		this->countPoppingX = 0;
		this->startPoppingY = this->getY();

		this->setVx(-float(0.5) * this->getOriginVx());
		this->setVy(-this->getOriginVy());
		break;
	}

	case GOOMBA_POPPING_RIGHT:
	{
		//if (animation == NULL) {
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedFlying());
		//}

		this->countPoppingX = 0;
		this->startPoppingY = this->getY();

		this->setVx(float(0.5) * this->getOriginVx());
		this->setVy(-this->getOriginVy());
		break;
	}

	case GOOMBA_FLYING_LEFT:
	{
		//if (animation == NULL) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedFlying());
		//}
		
		countPopping = 0;
		countFlyingX = 0;
		startFlyingY = this->getY();
		countDownFromMovingToFlying = 40;

		this->setVx(-this->getOriginVx());
		this->setVy(-this->getOriginVy());
		break;
	}

	case GOOMBA_FLYING_RIGHT:
	{
		//if (animation == NULL) {
		delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedFlying());
		//}

		countPopping = 0;
		countFlyingX = 0;
		startFlyingY = this->getY();
		countDownFromMovingToFlying = 40;

		this->setVx(abs(this->getOriginVx()));
		this->setVy(-abs(this->getOriginVy()));
		break;
	}

	case GOOMBA_DROPPING_LEFT_FROM_AIR:
	{

		this->setVx(-getOriginVx());
		this->setVy(getOriginVy());
		break;
	}

	case GOOMBA_DROPPING_RIGHT_FROM_AIR:
	{

		this->setVx(getOriginVx());
		this->setVy(getOriginVy());
		break;
	}

	case TRAMPLED_GOOMBA:
	{
		delete animation;
		if (this->isUseRedSkin) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedTrampled());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getTrampledGoomba());
		}
		this->setVx(0);
		break;
	}

	case THROWN_LEFT_AWAY_GOOMBA:
	{
		delete animation;
		if (this->isUseRedSkin) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedThrownAway());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getThrownAwayGoomba());
		}

		this->setVx(-getOriginVx());
		//this->setVy(-1.2 * getOriginVy());
		this->setVy(0);
		this->thrownX = 0;
		this->startThrownY = this->getY();
		break;
	}

	case THROWN_RIGHT_AWAY_GOOMBA:
	{
		delete animation;
		if (this->isUseRedSkin) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaRedThrownAway());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getThrownAwayGoomba());
		}
		this->setVx(getOriginVx());
		//this->setVy(-1.2 * getOriginVy());
		this->setVy(0);
		this->thrownX = 0;
		this->startThrownY = this->getY();
		break;
	}

	case DEAD_GOOMBA:
	{
		if (this->getState() == TRAMPLED_GOOMBA) {
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

void Goomba::setIsFlyingMode(bool _isFlyingMode)
{
	this->isFlyingMode = _isFlyingMode;
}

void Goomba::setMarioX(float _marioX)
{
	this->marioX = _marioX;
}

//void Goomba::setStoredVy(float _storedVy)
//{
//	this->storedVy = _storedVy;
//}

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
		/*if (this->getX() + this->getVx() * _dt >= 0
		&& this->getX() + this->getWidth() + this->getVx() * _dt <= Camera::getInstance()->getLimitX()) {*/
 			this->plusXNoRound(this->getVx() * _dt);
		//}
		if (this->getIsFlyingMode()) {
			if (countDownFromMovingToFlying <= 0) {
				if (this->getMarioX() < this->getX()) {
					this->setState(GoombaState::GOOMBA_POPPING_LEFT);
				}
				else {
					this->setState(GoombaState::GOOMBA_POPPING_RIGHT);
				}
			}
			--countDownFromMovingToFlying;
		}
	}
	else if (this->getState() == GOOMBA_DROPPING_LEFT || this->getState() == GOOMBA_DROPPING_RIGHT) {
		/*if (this->getX() + this->getVx() * _dt >= 0
			&& this->getX() + this->getWidth() + this->getVx() * _dt <= Camera::getInstance()->getLimitX()) {*/
			this->plusXNoRound(this->getVx() * _dt);
		//}
		this->plusYNoRound(this->getVy() * _dt);
	}
	else if (this->getState() == GOOMBA_POPPING_LEFT) {
		// vx now is < 0
		this->countPoppingX += (this->getVx() * _dt);
		float moreY = (-1 * (16 - (float(pow(countPoppingX + 8, 2)) / 4)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startPoppingY + moreY);

		if (countPoppingX < -8) {
			this->setVy(this->getOriginVy());
		}
	}
	else if (this->getState() == GOOMBA_POPPING_RIGHT) {
		// vx now is > 0
		this->countPoppingX += (this->getVx() * _dt);
		float moreY = (-1 * (16 - (float(pow(countPoppingX - 8, 2)) / 4)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startPoppingY + moreY);

		if (countPoppingX > 8) {
			this->setVy(this->getOriginVy());
		}
	}
	else if (this->getState() == GOOMBA_FLYING_LEFT) {
		// vx now is < 0
		countFlyingX += (this->getVx() * _dt);
		float moreY = (-1 * (32 - (float(pow(countFlyingX + 24, 2)) / 18)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX < -24) {
			this->setVy(abs(this->getOriginVy()));
		}
	}
	else if (this->getState() == GOOMBA_FLYING_RIGHT) {
		// vx now is > 0
		countFlyingX += (this->getVx() * _dt);
		float moreY = (-1 * (32 - (float(pow(countFlyingX - 24, 2)) / 18)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX > 24) {
			this->setVy(abs(this->getOriginVy()));
		}
	}
	else if (this->getState() == GOOMBA_DROPPING_LEFT_FROM_AIR || this->getState() == GOOMBA_DROPPING_RIGHT_FROM_AIR) {
		this->plusXNoRound(this->getVx() * _dt);
		this->plusYNoRound(this->getVy() * _dt);
	}
	else if (this->getState() == TRAMPLED_GOOMBA) {
		if (countDownToDead <= 0) {
			this->setState(GoombaState::DEAD_GOOMBA);
		}

		--countDownToDead;

		return;
	}
	else if (this->getState() == THROWN_LEFT_AWAY_GOOMBA) {
		this->plusXNoRound(-2);
		this->setY(this->startThrownY + (-1 * (16 - (float(pow(thrownX + 24, 2)) / 36)))); // -1: Oxy in game vs math
		thrownX -= (2);
	}
	else if (this->getState() == THROWN_RIGHT_AWAY_GOOMBA) {
		this->plusXNoRound(2);
		this->setY(this->startThrownY + (-1 * (16 - (float(pow(thrownX - 24, 2) / 36))))); // -1: Oxy in game vs math
		thrownX += (2);
	}
	this->animation->Update(_dt);
}

void Goomba::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == DEAD_GOOMBA) return;
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), D3DXVECTOR2(-4, -8));

	if (Setting::getInstance()->getDebugMode()) {
		Drawing::getInstance()->drawDebugBox(this->getBounds(), NULL, this->getPosition());
	}
}

void Goomba::handleHardComponentCollision(Component* _component, float _dt)
{
	if (this->getState() == TRAMPLED_GOOMBA
		|| this->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| this->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| this->getState() == DEAD_GOOMBA) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_component, _dt);
	if (get<0>(collisionResult) == true) {
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _component->getY()) {
				if (this->getState() == GOOMBA_MOVING_LEFT) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
				}
				else if (this->getState() == GOOMBA_DROPPING_LEFT) {
					this->setState(GoombaState::GOOMBA_DROPPING_RIGHT);
				}
				else if (this->getState() == GOOMBA_FLYING_LEFT || this->getState() == GOOMBA_POPPING_LEFT) {
					this->setState(GoombaState::GOOMBA_DROPPING_RIGHT_FROM_AIR);
				}
			}
			else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _component->getY()) {
				if (this->getState() == GOOMBA_MOVING_RIGHT) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
				}
				else if (this->getState() == GOOMBA_DROPPING_RIGHT) {
					this->setState(GoombaState::GOOMBA_DROPPING_LEFT);
				}
				else if (this->getState() == GOOMBA_FLYING_RIGHT || this->getState() == GOOMBA_POPPING_RIGHT) {
					this->setState(GoombaState::GOOMBA_DROPPING_LEFT_FROM_AIR);
				}
			}
			else if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == GOOMBA_DROPPING_LEFT) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
					this->setY(_component->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_DROPPING_RIGHT) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
					this->setY(_component->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_POPPING_LEFT) {
					++countPopping;

					if (countPopping >= 3) {
						this->setState(GoombaState::GOOMBA_FLYING_LEFT);
					}
					else {
						this->setState(GoombaState::GOOMBA_POPPING_LEFT);
					}

					this->setY(_component->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_POPPING_RIGHT) {
					++countPopping;

					if (countPopping >= 3) {
						this->setState(GoombaState::GOOMBA_FLYING_RIGHT);
					}
					else {
						this->setState(GoombaState::GOOMBA_POPPING_RIGHT);
					}

					this->setY(_component->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_FLYING_LEFT) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
					this->setY(_component->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_FLYING_RIGHT) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
					this->setY(_component->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_DROPPING_LEFT_FROM_AIR) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
					countDownFromMovingToFlying = 40;
					this->setY(_component->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_DROPPING_RIGHT_FROM_AIR) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
					countDownFromMovingToFlying = 40;
					this->setY(_component->getY() - this->getBoundsHeight());
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
					if (this->getY() + this->getBoundsHeight() == _component->getY()) {
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

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_block, _dt);
	if (get<0>(collisionResult) == true) {
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == GOOMBA_DROPPING_LEFT) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
					this->setY(_block->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_DROPPING_RIGHT) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
					this->setY(_block->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_POPPING_LEFT) {
					++countPopping;

					if (countPopping >= 3) {
						this->setState(GoombaState::GOOMBA_FLYING_LEFT);
					}
					else {
						this->setState(GoombaState::GOOMBA_POPPING_LEFT);
					}

					this->setY(_block->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_POPPING_RIGHT) {
					if (countPopping >= 3) {
						this->setState(GoombaState::GOOMBA_FLYING_RIGHT);
					}
					else {
						this->setState(GoombaState::GOOMBA_POPPING_RIGHT);
					}

					this->setY(_block->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_FLYING_LEFT) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
					this->setY(_block->getY() - this->getBoundsHeight());
				}
				else if (this->getState() == GOOMBA_FLYING_RIGHT) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
					this->setY(_block->getY() - this->getBoundsHeight());
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
					if (this->getY() + this->getBoundsHeight() == _block->getY()) {
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
				/*|| _koopa->getState() == KOOPA_DROPPING_LEFT
				|| _koopa->getState() == KOOPA_DROPPING_RIGHT*/) {
				_koopa->plusX(_koopa->getVx() * get<1>(collisionResult));
				_koopa->plusY(_koopa->getVy() * get<1>(collisionResult));
				_koopa->convertMovingState();

				this->plusX(this->getVx() * get<1>(collisionResult));
				this->plusY(this->getVy() * get<1>(collisionResult));
				this->convertMovingState();
			}
			else if (_koopa->getState() == KOOPA_SHRINKAGE_MOVING_LEFT
				|| _koopa->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
				|| _koopa->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT
				|| _koopa->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint(), this->getX(), this->getY())));
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
		else {
			if (_koopa->getState() == KOOPA_SHRINKAGE_MOVING_LEFT
				|| _koopa->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
				|| _koopa->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT
				|| _koopa->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint(), this->getX(), this->getY())));
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
}

void Goomba::handleMarioCollision(Mario* _mario, float _dt)
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

	if (this->getState() == TRAMPLED_GOOMBA
		|| this->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| this->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| this->getState() == DEAD_GOOMBA) {
		return;
	}

	// When mario turning around
	if (_mario->getIsTurningAround()) {
		if (get<0>(_mario->sweptAABBByFrame(this, _dt)) || _mario->isCollidingByFrame(this->getFrame())) {
			if (_mario->getIsFlip()) { // <--
				if (this->getX() <= _mario->getX()
					&& this->getX() + this->getWidth() >= _mario->getX() - _mario->getLeftSpace()
					&& _mario->getBounds().top + _mario->getTailMarginTop() >= this->getY()
					&& _mario->getBounds().bottom - _mario->getTailMarginBottom() <= this->getY() + this->getHeight()) {
					this->setState(GoombaState::THROWN_LEFT_AWAY_GOOMBA);

					ScoreBoard::getInstance()->plusPoint(this->getDefaultPoint());
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint(), this->getX(), this->getY())));
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), this->getX(), this->getY())));
					return;
				}
			}
			else { // -->
				if (this->getX() >= _mario->getX()
					&& this->getX() <= _mario->getX() + _mario->getBoundsWidth() + _mario->getLeftSpace()
					&& _mario->getBounds().top + _mario->getTailMarginTop() >= this->getY()
					&& _mario->getBounds().bottom - _mario->getTailMarginBottom() <= this->getY() + this->getHeight()) {
					this->setState(GoombaState::THROWN_RIGHT_AWAY_GOOMBA);

					ScoreBoard::getInstance()->plusPoint(this->getDefaultPoint());
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint(), this->getX(), this->getY())));
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), this->getX(), this->getY())));
					return;
				}
			}
		}
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	/*if (this->getState() == GOOMBA_FLYING_LEFT || this->getState() == GOOMBA_FLYING_RIGHT || this->getState() == GOOMBA_DROPPING_LEFT || this->getState() == GOOMBA_DROPPING_RIGHT) {
		this->setVy(this->getStoredVy());
	}*/

	if (get<0>(collisionResult) == true) {
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				//this->plusY(2 * get<1>(collisionResult) * this->getVy());
				_mario->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * this->getVx());
				this->plusY(get<1>(collisionResult) * this->getVy());
			}
			else if (edge == leftEdge) {
				//this->plusX(2 * get<1>(collisionResult) * this->getVx());
				_mario->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * this->getVx());
				this->plusY(get<1>(collisionResult) * this->getVy());
			}
			else if (edge == rightEdge) {
				//this->plusX(2 * get<1>(collisionResult) * this->getVx());
				_mario->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * this->getVx());
				this->plusY(get<1>(collisionResult) * this->getVy());
			}
			else if (edge == topEdge && _mario->getState() == DROPPING) {
				_mario->setState(MarioState::JUMPING);
				//_mario->plusY(get<1>(collisionResult) * _mario->getVy() + this->getHeight() / 4);
				
				if (this->getIsFlyingMode()) {
					if (this->getState() == GOOMBA_FLYING_LEFT || this->getState() == GOOMBA_POPPING_LEFT) {
						//this->plusY(2 * get<1>(collisionResult) * abs(_mario->getVy()));
						this->setIsFlyingMode(false);
						this->setState(GoombaState::GOOMBA_DROPPING_LEFT);
					}
					else if (this->getState() == GOOMBA_FLYING_RIGHT || this->getState() == GOOMBA_POPPING_RIGHT) {
						//this->plusY(2 * get<1>(collisionResult) * abs(_mario->getVy()));
						this->setIsFlyingMode(false);
						this->setState(GoombaState::GOOMBA_DROPPING_RIGHT);
					}
					else if (this->getState() == GOOMBA_MOVING_LEFT) {
						this->setIsFlyingMode(false);
						this->setState(GoombaState::GOOMBA_MOVING_LEFT);
					}
					else if (this->getState() == GOOMBA_MOVING_RIGHT) {
						this->setIsFlyingMode(false);
						this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
					}
				}
				else {
					this->setState(GoombaState::TRAMPLED_GOOMBA);
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint() * this->getPointCoef(), this->getX(), this->getY())));
				}

				// Calculate points
				_mario->increasePointCoef();
				this->setPointCoef(_mario->getPointCoef());
				ScoreBoard::getInstance()->plusPoint(this->getDefaultPoint() * this->getPointCoef());
			}
		}
	}
	else if (this->isCollidingByBounds(_mario->getBounds())) {
		if (_mario->getState() == WALKING || _mario->getState() == STANDING) {
			_mario->setState(MarioState::DIE);
		}
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

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_fireBall, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByFrame(_fireBall->getFrame())) {
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
