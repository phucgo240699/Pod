#include "Koopa.h"
#include "Mario.h"
#include "Goomba.h"

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
	this->originVx = this->getVx();
	this->originVy = this->getVy();
	this->defaultPoint = v[4];
	this->setId(v[5]);

	this->setIsGreenMode(v[6] == 1);

	if (this->getIsGreenMode() == false) {
		this->leftAnchor = v[7];
		this->rightAnchor = v[8];
	}
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

bool Koopa::getIsGreenMode()
{
	return this->isGreenMode;
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
	{
		if (this->animation == NULL) {
			delete animation;
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaMoving());
			}
		}
		this->setVx(0);
		this->setVy(0);
		break;
	}
	case KOOPA_MOVING_LEFT:
	{
		if (this->getState() == KOOPA_SHRINKAGE_SHAKING || this->animation == NULL) {
			delete animation;
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaMoving());
			}
		}
		this->setIsFlip(true);
		this->setVx(-abs(this->originVx));
		this->setVy(0);
		break;
	}

	case KOOPA_MOVING_RIGHT:
	{
		if (this->getState() == KOOPA_SHRINKAGE_SHAKING || this->animation == NULL) {
			delete animation;
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaMoving());
			}
		}
		this->setIsFlip(false);
		this->setVx(abs(this->originVx));
		this->setVy(0);
		break;
	}

	case KOOPA_DROPPING_LEFT:
	{
		if (this->getState() == KOOPA_SHRINKAGE_SHAKING || this->animation == NULL) {
			delete animation;
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaMoving());
			}
		}
		this->setIsFlip(true);
		this->setVx(-abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	}

	case KOOPA_DROPPING_RIGHT:
	{
		if (this->getState() == KOOPA_SHRINKAGE_SHAKING || this->animation == NULL) {
			delete animation;
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaMoving());
			}
		}
		this->setIsFlip(true);
		this->setVx(abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	}

	case KOOPA_SHRINKAGE:
	{
		delete animation;
		if (this->getIsGreenMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenShrinkage());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkage());
		}
		//this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));
		this->setVx(0);
		this->setVy(0);
		break;
	}

	case KOOPA_SHRINKAGE_MOVING_LEFT:
	{
		if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
			delete animation;
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenShrinkageMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageMoving());
			}
			//this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));
		}
		this->setIsFlip(true);
		this->setVx(-6 * abs(this->originVx));
		this->setVy(0);
		break;
	}

	case KOOPA_SHRINKAGE_MOVING_RIGHT:
	{
		if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
			delete animation;
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenShrinkageMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageMoving());
			}
			//this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));
		}
		this->setIsFlip(false);
		this->setVx(6 * abs(this->originVx));
		this->setVy(0);
		break;
	}

	case KOOPA_SHRINKAGE_DROPPING_LEFT:
	{
		if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
			delete animation;
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenShrinkageMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageMoving());
			}
			//this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));
		}
		this->setIsFlip(true);
		this->setVx(-6 * abs(this->originVx));
		this->setVy(2 * abs(this->originVy));
		break;
	}

	case KOOPA_SHRINKAGE_DROPPING_RIGHT:
	{
		if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
			delete animation;
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenShrinkageMoving());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageMoving());
			}
			//this->pointAnimation = Animation(AnimationBundle::getInstance()->getPoints(this->getDefaultPoint() * this->getPointCoef()));
		}
		this->setIsFlip(true);
		this->setVx(6 * abs(this->originVx));
		this->setVy(2 * abs(this->originVy));
		break;
	}

	case KOOPA_SHRINKAGE_SHAKING:
	{
		delete animation;
		if (this->getIsGreenMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenShrinkageShaking());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkageShaking());
		}
		this->setVx(0);
		this->setVy(0);
		break;
	}
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

void Koopa::setupPointAnimPosition()
{
	AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(this->getDefaultPoint() * this->getPointCoef(), this->getX(), this->getY())));
}

void Koopa::setHasCollideMario(bool _hasCollideMario)
{
	this->hasCollideMario = _hasCollideMario;
}

void Koopa::setIsGreenMode(bool _isGreenMode)
{
	this->isGreenMode = _isGreenMode;
}

void Koopa::convertMovingState()
{
	if (this->getState() == KOOPA_MOVING_LEFT) {
		this->setState(KoopaState::KOOPA_MOVING_RIGHT);
	}
	else if (this->getState() == KOOPA_MOVING_RIGHT) {
		this->setState(KoopaState::KOOPA_MOVING_LEFT);
	}
	else if (this->getState() == KOOPA_DROPPING_LEFT) {
		this->setState(KoopaState::KOOPA_DROPPING_RIGHT);
	}
	else if (this->getState() == KOOPA_DROPPING_RIGHT) {
		this->setState(KoopaState::KOOPA_DROPPING_LEFT);
	}
	else if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
		this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
	}
	else if (this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
		this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
	}
	else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
		this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
	}
	else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
		this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
	}
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
		if (this->getIsGreenMode() == false && this->getX() + this->getVx() * _dt < this->leftAnchor) {
			this->setX(this->leftAnchor);
			this->setState(KoopaState::KOOPA_MOVING_RIGHT);
		}

		this->plusXNoRound(this->getVx() * _dt);
	}
	else if (this->getState() == KOOPA_MOVING_RIGHT) {
		if (this->getIsGreenMode() == false && this->getX() + this->getWidth() + this->getVx() * _dt > this->rightAnchor) {
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
	else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT || this->getState() == KOOPA_DROPPING_LEFT) {
		this->plusXNoRound(this->getVx() * _dt);
		this->plusYNoRound(this->getVy() * _dt);
	}
	else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT || this->getState() == KOOPA_DROPPING_RIGHT) {
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

	/*if (this->pointY == this->endPointJumpUp || this->pointY == -std::numeric_limits<float>::infinity()) {
		return;
	}

	if (this->pointY - (2 * _dt) >= this->endPointJumpUp) {
		this->pointY -= (2 * _dt);
	}
	else {
		this->pointY = this->endPointJumpUp;
	}*/
}

void Koopa::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == KOOPA_DEAD) return;
	if (this->animation != NULL) {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), this->getIsFlip());
	}
	/*if (this->pointY == this->endPointJumpUp || this->pointY == -std::numeric_limits<float>::infinity()) {
		return;
	}*/
	//Drawing::getInstance()->draw(_texture, this->pointAnimation.getCurrentFrame(), D3DXVECTOR3(this->pointX, this->pointY, 0));
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
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_DROPPING_LEFT) {
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}

			this->setY(_component->getY() - this->getHeight());
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
		if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT
			|| this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
			|| this->getState() == KOOPA_MOVING_LEFT
			|| this->getState() == KOOPA_MOVING_RIGHT) {
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

void Koopa::handleGiftBrickCollision(GiftBrick* _giftBrick, Mario* _mario, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_giftBrick, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == bottomEdge) {
			this->setIsStandOnSurface(true);
			this->leftAnchor = _giftBrick->getX();
			this->rightAnchor = _giftBrick->getX() + _giftBrick->getWidth();

			if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_DROPPING_LEFT) {
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}

			this->setY(_giftBrick->getY() - this->getHeight());
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
			this->plusX(get<1>(collisionResult) * this->getVx());

			if (_giftBrick->getState() == FULLGIFTBRICK) {
				if (_giftBrick->getGiftType() == NotPoint) {
					if (_mario->getIsSuperMode() == false) {
						_giftBrick->setGiftType(GiftType::SuperMushroomGift);
					}
					else {
						_giftBrick->plusY(_mario->getVy() * _dt + (_giftBrick->getHeight() / 2));
						_giftBrick->setGiftType(GiftType::SuperLeafGift);
					}
				}
				_giftBrick->setState(GiftBrickState::POPUPGIFTBRICK);
				if (_giftBrick->getGiftType() == Point100Gift) {
					ScoreBoard::getInstance()->plusCoin(1);
					ScoreBoard::getInstance()->plusPoint(100);
				}
			}
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
			this->plusX(get<1>(collisionResult) * this->getVx());

			if (_giftBrick->getState() == FULLGIFTBRICK) {
				if (_giftBrick->getGiftType() == NotPoint) {
					if (_mario->getIsSuperMode() == false) {
						_giftBrick->setGiftType(GiftType::SuperMushroomGift);
					}
					else {
						_giftBrick->plusY(_mario->getVy() * _dt + (_giftBrick->getHeight() / 2));
						_giftBrick->setGiftType(GiftType::SuperLeafGift);
					}
				}
				_giftBrick->setState(GiftBrickState::POPUPGIFTBRICK);
				if (_giftBrick->getGiftType() == Point100Gift) {
					ScoreBoard::getInstance()->plusCoin(1);
					ScoreBoard::getInstance()->plusPoint(100);
				}
			}
		}
	}
	else {
		// if supermushroom walk out of ground's top surface, it will drop
		if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT
			|| this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
			|| this->getState() == KOOPA_MOVING_LEFT
			|| this->getState() == KOOPA_MOVING_RIGHT) {
			if (this->getIsStandOnSurface() == false) {
				if ((_giftBrick->getX() <= this->getX() + this->getWidth() && this->getX() + this->getWidth() <= _giftBrick->getX() + _giftBrick->getWidth())
					|| (_giftBrick->getX() <= this->getX() && this->getX() <= _giftBrick->getX() + _giftBrick->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getHeight() == _giftBrick->getY()) {
						this->setIsStandOnSurface(true);
						this->leftAnchor = _giftBrick->getX();
						this->rightAnchor = _giftBrick->getX() + _giftBrick->getWidth();
					}
				}
			}
		}
	}
}

void Koopa::handleBlockCollision(Component* _block, float _dt)
{
	//if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT || this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
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
			if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT
				|| this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
				|| this->getState() == KOOPA_MOVING_LEFT
				|| this->getState() == KOOPA_MOVING_RIGHT) {
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
	//}
}

void Koopa::handleGoombaCollision(Goomba* _goomba, float _dt)
{
	if (_goomba->getState() == TRAMPLED_GOOMBA
		|| _goomba->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| _goomba->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| _goomba->getState() == DEAD_GOOMBA) {
		return;
	}
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_goomba, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == leftEdge || edge == rightEdge) {
			if (this->getState() == KOOPA_MOVING_LEFT
				|| this->getState() == KOOPA_MOVING_RIGHT
				|| this->getState() == KOOPA_DROPPING_LEFT
				|| this->getState() == KOOPA_DROPPING_RIGHT) {
				this->convertMovingState();
				_goomba->convertMovingState();
			}
			else {
				AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_goomba->getDefaultPoint() * _goomba->getPointCoef(), _goomba->getX(), _goomba->getY())));
				AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(_goomba->getX(), _goomba->getY())));

				if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT
					|| this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
					_goomba->setState(GoombaState::THROWN_LEFT_AWAY_GOOMBA);
				}
				else if (this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
					|| this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
					_goomba->setState(GoombaState::THROWN_RIGHT_AWAY_GOOMBA);
				}
			}
		}
	}
}

void Koopa::handleMarioCollision(Mario* _mario, float _dt)
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

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);
	if (get<0>(collisionResult) == true) {
			CollisionEdge edge = get<2>(collisionResult)[0];
			if (edge == leftEdge) {
				if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
					this->plusX(_mario->getVx() * _dt + 2);
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
					//_mario->plusX(get<1>(collisionResult) * _mario->getVx());
				}
				else {
					if (_mario->getIsSuperMode() == false) {
						this->plusX(get<1>(collisionResult) * this->getVx());
						this->setState(KoopaState::KOOPA_STANDING);
					}
					_mario->setState(MarioState::DIE);
					this->plusX(get<1>(collisionResult) * this->getVx());
				}
			}
			else if (edge == rightEdge) {
				if (this->getState() == KOOPA_SHRINKAGE || this->getState() == KOOPA_SHRINKAGE_SHAKING) {
					this->plusX(_mario->getVx() * _dt - 2);
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
					//_mario->plusX(get<1>(collisionResult) * _mario->getVx());
				}
				else {
					if (_mario->getIsSuperMode() == false) {
						this->plusX(get<1>(collisionResult) * this->getVx());
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
				_mario->plusY(get<1>(collisionResult) * _mario->getVy() + this->getHeight() / 4);
				_mario->setState(MarioState::JUMPING);

				// Calculate points
				_mario->increasePointCoef();
				this->setPointCoef(_mario->getPointCoef());
				ScoreBoard::getInstance()->plusPoint(this->getDefaultPoint() * this->getPointCoef());

				if (this->getState() == KOOPA_SHRINKAGE) {
					float centerMario = _mario->getX() + _mario->getBoundsWidth() / 2;
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