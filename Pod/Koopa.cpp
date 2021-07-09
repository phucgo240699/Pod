#include "Koopa.h"
#include "Mario.h"

Koopa::Koopa(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

Koopa::Koopa(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_position, _vx, _vy, _limitX, _limitY)
{
}

void Koopa::loadInfo(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(v[2]);
	this->setVy(v[3]);
	this->leftAnchor = v[4];
	this->rightAnchor = v[5];
	this->defaultPoint = v[6];
	this->setId(v[7]);

	this->originVx = this->getVx();
	this->originVy = this->getVy();
}

KoopaState Koopa::getState()
{
	return this->state;
}

float Koopa::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float Koopa::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

bool Koopa::getIsFlip()
{
	return this->isFlip;
}

bool Koopa::getIsStandOnSurface()
{
	return this->isStandOnSurface;
}

bool Koopa::getHasCollideMario()
{
	return this->hasCollideMario;
}

void Koopa::setState(KoopaState _state)
{
	if (this->animation != NULL) {
		this->oldFrameWidth = this->animation->getCurrentFrameWidth();
		this->oldFrameHeight = this->animation->getCurrentFrameHeight();
	}

	switch (_state)
	{
	case KOOPA_STANDING:
		if (this->animation == NULL) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaMoving());
		}
		this->setVx(0);
		this->setVy(0);
		break;
	case KOOPA_MOVING_LEFT:
		if (this->getState() == KOOPA_SHRINKAGE_SHAKING || this->animation == NULL) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaMoving());
		}
		this->setIsFlip(true);
		this->setVx(-1 * abs(this->originVx));
		this->setVy(0);
		break;
	case KOOPA_MOVING_RIGHT:
		if (this->getState() == KOOPA_SHRINKAGE_SHAKING || this->animation == NULL) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaMoving());
		}
		this->setIsFlip(false);
		this->setVx(abs(this->originVx));
		this->setVy(0);
		break;
	case KOOPA_SHRINKAGE:
	{
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkage());
		this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));

		this->setVx(0);
		this->setVy(0);
	}
		break;

	case KOOPA_SHRINKAGE_MOVING_LEFT:
		if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageMoving());
			this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));
		}
		this->setIsFlip(true);
		this->setVx(-6 * abs(this->originVx));
		this->setVy(0);
		break;

	case KOOPA_SHRINKAGE_MOVING_RIGHT:
		if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageMoving());
			this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));
		}
		this->setIsFlip(false);
		this->setVx(6 * abs(this->originVx));
		this->setVy(0);
		break;

	case KOOPA_SHRINKAGE_DROPPING_LEFT:
		if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageMoving());
			this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));
		}
		this->setIsFlip(true);
		this->setVx(-6 * abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;

	case KOOPA_SHRINKAGE_DROPPING_RIGHT:
		if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageMoving());
			this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));
		}
		this->setIsFlip(true);
		this->setVx(6 * abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;

	case KOOPA_SHRINKAGE_SHAKING:
		delete animation;
		this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageShaking());
		this->setVx(0);
		this->setVy(0);
		break;
	}

	this->state = _state;

	if (firstCheckAnim == false) {
		this->newFrameWidth = this->animation->getCurrentFrameWidth();
		this->newFrameHeight = this->animation->getCurrentFrameHeight();

		if (oldFrameWidth != newFrameWidth) {
			this->plusX(oldFrameWidth - newFrameWidth);
		}
		if (oldFrameHeight != newFrameHeight) {
			this->plusY(oldFrameHeight - newFrameHeight);
		}
	}

	firstCheckAnim = false;
}

void Koopa::setIsFlip(bool _isFlip)
{
	this->isFlip = _isFlip;
}

void Koopa::setPointX(float _pointX)
{
	this->pointX = _pointX;
}

void Koopa::setPointY(float _pointY)
{
	this->pointY = _pointY;
}

void Koopa::setEndPointJumpUp(float _endPointJumpUp)
{
	this->endPointJumpUp = _endPointJumpUp;
}

void Koopa::setupPointAnimPosition()
{
	this->pointX = this->getX();
	this->pointY = this->getY() - this->pointAnimation.getCurrentFrameHeight();
	this->endPointJumpUp = this->getY() - this->pointAnimation.getCurrentFrameHeight() - 48;
}

void Koopa::setHasCollideMario(bool _hasCollideMario)
{
	this->hasCollideMario = _hasCollideMario;
}

void Koopa::Update(float _dt)
{
	if (this->getState() == KOOPA_DEAD || this->getState() == KOOPA_STANDING) return;
	
	Enemy::Update(_dt);

	if (this->getIsStandOnSurface() == true) {
		this->setIsStandOnSurface(false);
	}

	this->animation->Update(_dt);

	if (this->getState() == KOOPA_MOVING_LEFT) {
		if (this->getX() + this->getVx() * _dt < this->leftAnchor) {
			this->setX(this->leftAnchor);
			this->setState(KoopaState::KOOPA_MOVING_RIGHT);
		}

		this->plusXNoRound(this->getVx() * _dt);
	}
	else if (this->getState() == KOOPA_MOVING_RIGHT) {
		if (this->getX() + this->getWidth() + this->getVx() * _dt > this->rightAnchor) {
			this->setX(this->rightAnchor - this->getWidth());
			this->setState(KoopaState::KOOPA_MOVING_LEFT);
		}

		this->plusXNoRound(this->getVx() * _dt);
	}
	else if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
		this->plusXNoRound(this->getVx() * _dt);
	}
	else if (this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
		this->plusXNoRound(this->getVx() * _dt);
	}
	else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
		this->plusXNoRound(this->getVx() * _dt);
		this->plusYNoRound(this->getVy() * _dt);
	}
	else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
		this->plusXNoRound(this->getVx() * _dt);
		this->plusYNoRound(this->getVy() * _dt);
	}
	else if (this->getState() == KOOPA_SHRINKAGE) {
		if (this->animation->getCurrentIndexFrame() == this->animation->getTotalFrames() - 1
			&& this->animation->getAnimCount() >= this->animation->getAnimDelay()) {
			this->setState(KoopaState::KOOPA_SHRINKAGE_SHAKING);
		}
	}
	else if (this->getState() == KOOPA_SHRINKAGE_SHAKING) {
		if (this->animation->getCurrentIndexFrame() == this->animation->getTotalFrames() - 1
			&& this->animation->getAnimCount() >= this->animation->getAnimDelay()) {
			// TODO: Now set state to moving => problem: range moving...
			
			int random = rand() % 2 + 1;
			if (random == 1) {
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}
			else {
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
		}
	}

	if (this->pointY == this->endPointJumpUp || this->pointY == -std::numeric_limits<float>::infinity()) {
		return;
	}
	//this->pointAnimation.Update(_dt);
	if (this->pointY - (2 * _dt) >= this->endPointJumpUp) {
		this->pointY -= (2 * _dt);
	}
	else {
		this->pointY = this->endPointJumpUp;
	}


	// update which cell in grid that it's belongs to
	Grid::getInstance()->updateCellOf(this);
}

void Koopa::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == KOOPA_DEAD) return;
	if (this->animation != NULL) {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), this->getIsFlip());
	}
	if (this->pointY == this->endPointJumpUp || this->pointY == -std::numeric_limits<float>::infinity()) {
		return;
	}
	Drawing::getInstance()->draw(_texture, this->pointAnimation.getCurrentFrame(), D3DXVECTOR3(this->pointX, this->pointY, 0));
}

void Koopa::handleHardComponentCollision(Component* _component, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_component, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == bottomEdge) {
			this->setIsStandOnSurface(true);
			this->leftAnchor = _component->getX();
			this->rightAnchor = _component->getX() + _component->getWidth();
			if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				this->setY(_component->getY() - this->getHeight());
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
				this->setY(_component->getY() - this->getHeight());
			}
		}
		else if (edge == leftEdge) {
			if (this->getState() == KOOPA_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
			}
			this->plusX(get<1>(collisionResult)* this->getVx());
		}
		else if (edge == rightEdge) {
			if (this->getState() == KOOPA_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
			}
			this->plusX(get<1>(collisionResult)* this->getVx());
		}
	}
	else {
		// if supermushroom walk out of ground's top surface, it will drop
		if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT || this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
			if (this->getIsStandOnSurface() == false) {
				if ((_component->getX() <= this->getX() + this->getWidth() && this->getX() + this->getWidth() <= _component->getX() + _component->getWidth())
					|| (_component->getX() <= this->getX() && this->getX() <= _component->getX() + _component->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getHeight() == _component->getY()) {
						this->setIsStandOnSurface(true);
						this->leftAnchor = _component->getX();
						this->rightAnchor = _component->getX() + _component->getWidth();
					}
				}
			}
		}
	}
}

void Koopa::handleBlockCollision(Component* _block, float _dt)
{
	if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT || this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
		tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_block, _dt);
		if (get<0>(collisionResult) == true) {
			CollisionEdge edge = get<2>(collisionResult)[0];
			if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				this->leftAnchor = _block->getX();
				this->rightAnchor = _block->getX() + _block->getWidth();

				if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
					this->plusYNoRound(this->getVy() * get<1>(collisionResult));
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				}
				else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
					this->plusYNoRound(this->getVy() * get<1>(collisionResult));
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
				}
			}
			//}
		}
		else {
			// if supermushroom walk out of ground's top surface, it will drop
			if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT || this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
				if (this->getIsStandOnSurface() == false) {
					if ((_block->getX() <= this->getX() + this->getWidth() && this->getX() + this->getWidth() <= _block->getX() + _block->getWidth())
						|| (_block->getX() <= this->getX() && this->getX() <= _block->getX() + _block->getWidth())) { // this is check which ground that mario is standing on
						if (this->getY() + this->getHeight() == _block->getY()) {
							this->setIsStandOnSurface(true);
							this->leftAnchor = _block->getX();
							this->rightAnchor = _block->getX() + _block->getWidth();
						}
					}
				}
			}
		}
	}
}

void Koopa::handleMarioCollision(Mario* _mario, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);
	if (get<0>(collisionResult) == true) {
			CollisionEdge edge = get<2>(collisionResult)[0];
			if (edge == leftEdge) {
				if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
					this->plusX(_mario->getVx() * _dt);
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
					_mario->plusX(get<1>(collisionResult) * _mario->getVx());
				}
				else {
					if (_mario->getIsSuperMode() == false) {
						this->setState(KoopaState::KOOPA_STANDING);
					}
					_mario->setState(MarioState::DIE);
					this->plusX(get<1>(collisionResult) * this->getVx());
				}
			}
			else if (edge == rightEdge) {
				if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
					this->plusX(_mario->getVx() * _dt);
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
					_mario->plusX(get<1>(collisionResult) * _mario->getVx());
				}
				else {
					if (_mario->getIsSuperMode() == false) {
						this->setState(KoopaState::KOOPA_STANDING);
					}
					_mario->setState(MarioState::DIE);
					this->plusX(get<1>(collisionResult) * this->getVx());
				}
			}
			else if (edge == bottomEdge) {
				if (_mario->getIsSuperMode() == false) {
					this->setState(KoopaState::KOOPA_STANDING);
				}
				_mario->setState(MarioState::DIE);
			}
			else if (edge == topEdge && _mario->getState() == DROPPING) { // _mario->getState() == DROPPING: for prevenet conflict check collide from mario and from koopa
				_mario->plusY(get<1>(collisionResult) * _mario->getVy());
				_mario->setState(MarioState::JUMPING);

				// Calculate points
				_mario->increasePointCoef();
				this->setPointCoef(_mario->getPointCoef());
				ScoreBoard::getInstance()->plusPoint(this->getDefaultPoint() * this->getPointCoef());

				if (this->getState() == KOOPA_SHRINKAGE) {
					float centerMario = _mario->getX() + _mario->getWidth() / 2;
					float centerKoopa = this->getX() + this->getWidth() / 2;
					if (centerMario >= centerKoopa) {
						this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
					}
					else {
						this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
					}
				}
				else {
					this->setState(KoopaState::KOOPA_SHRINKAGE);
				}

				this->setupPointAnimPosition();
			}
	}
}