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
	this->setIsFlyingMode(v[6] == 2);
	if (this->getIsGreenMode() == false && this->getIsFlyingMode() == false) {
		isOutOfFirstStage = false;
	}
	

	if (this->getIsGreenMode() == false && this->getIsFlyingMode() == false) {
		this->leftAnchor = v[7];
		this->rightAnchor = v[8];
	}
}

RECT Koopa::getFrame()
{
	RECT r = RECT();
	r.top = this->getY() - 8;
	r.bottom = r.top + this->getHeight();
	r.left = this->getX() - 4;
	r.right = r.left + this->getWidth();

	return r;
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

float Koopa::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

float Koopa::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
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

bool Koopa::getIsFlyingMode()
{
	return this->isFlyingMode;
}

float Koopa::getOriginVy()
{
	return this->originVy;
}

float Koopa::getOriginVx()
{
	return this->originVx;
}

bool Koopa::getIsShrinkageReverseMode()
{
	return this->isShrinkageReverseMode;
}

bool Koopa::getIsOutOfFirstStage()
{
	return this->isOutOfFirstStage;
}

//float Koopa::getStoredVy()
//{
//	return this->storedVy;
//}

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
		else if (this->getState() == KOOPA_FLYING_LEFT || this->getState() == KOOPA_FLYING_RIGHT) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenMoving());
			this->setIsFlyingMode(false);
			this->setIsGreenMode(true);
		}
		
		this->isOutOfFirstStage = true;
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
		else if (this->getState() == KOOPA_FLYING_LEFT || this->getState() == KOOPA_FLYING_RIGHT) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenMoving());
			this->setIsFlyingMode(false);
			this->setIsGreenMode(true);
		}

		this->isOutOfFirstStage = true;
		this->setIsFlip(false);
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

		this->isOutOfFirstStage = true;
		this->setIsFlip(true);
		this->setVx(-4 * abs(this->originVx));
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

		this->isOutOfFirstStage = true;
		this->setIsFlip(false);
		this->setVx(4 * abs(this->originVx));
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

		this->isOutOfFirstStage = true;
		this->setIsFlip(true);
		this->setVx(-4 * abs(this->originVx));
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

		this->isOutOfFirstStage = true;
		this->setIsFlip(false);
		this->setVx(4 * abs(this->originVx));
		this->setVy(2 * abs(this->originVy));
		break;
	}

	case KOOPA_FLYING_LEFT:
	{
		if (this->getState() != KOOPA_FLYING_LEFT && this->getState() != KOOPA_FLYING_RIGHT) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaFlying());
		}
		countFlyingX = 0;
		startFlyingY = this->getY();
		this->setIsFlip(true);
		this->setVx(-1.4 * abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	}

	case KOOPA_FLYING_RIGHT:
	{
		if (this->getState() != KOOPA_FLYING_LEFT && this->getState() != KOOPA_FLYING_RIGHT) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaFlying());
		}
		countFlyingX = 0;
		startFlyingY = this->getY();
		this->setIsFlip(false);
		this->setVx(1.4 * abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	}

	case KOOPA_DROPPING_LEFT_FROM_AIR:
	{
		this->setIsFlip(true);
		this->setVx(-abs(this->originVx));
		this->setVy(abs(this->originVy));
		break;
	}

	case KOOPA_DROPPING_RIGHT_FROM_AIR:
	{
		this->setIsFlip(false);
		this->setVx(abs(this->originVx));
		this->setVy(abs(this->originVy));
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

	case KOOPA_THROWN_LEFT_TO_SHINKAGE:
	{
		delete animation;
		if (this->getIsGreenMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenShrinkage());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkage());
		}

		this->isOutOfFirstStage = true;
		this->setIsShrinkageReverseMode(true);
		this->setIsFlip(true);
		this->countThrownToShrinkageX = 0;
		this->startThrownToShrinkageY = this->getY();
		this->setVx(-0.4);// .5 * abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	}

	case KOOPA_THROWN_RIGHT_TO_SHINKAGE:
	{
		delete animation;
		if (this->getIsGreenMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenShrinkage());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaShrinkage());
		}

		this->isOutOfFirstStage = true;
		this->setIsShrinkageReverseMode(true);
		this->setIsFlip(false);
		this->countThrownToShrinkageX = 0;
		this->startThrownToShrinkageY = this->getY();
		this->setVx(0.4);// .5 * abs(this->originVx));
		this->setVy(-abs(this->originVy));
		break;
	}

	case KOOPA_THROWN_LEFT_AWAY:
	{
		delete animation;
		if (this->getIsGreenMode() || this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenThrownAway());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaRedThrownAway());
		}

		this->setIsFlip(true);
		this->thrownX = 0;
		this->startThrownY = this->getY();
		break;
	}

	case KOOPA_THROWN_RIGHT_AWAY:
	{
		delete animation;
		if (this->getIsGreenMode() || this->getIsFlyingMode()) {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaGreenThrownAway());
		}
		else {
			this->animation = new Animation(AnimationBundle::getInstance()->getKoopaRedThrownAway());
		}

		this->setIsFlip(false);
		this->thrownX = 0;
		this->startThrownY = this->getY();
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

void Koopa::setIsFlyingMode(bool _isFlyingMode)
{
	this->isFlyingMode = _isFlyingMode;
}

void Koopa::setIsShrinkageReverseMode(bool _value)
{
	this->isShrinkageReverseMode = _value;
}

//void Koopa::setStoredVy(float _storedVy)
//{
//	this->storedVy = _storedVy;
//}

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
	Enemy::Update(_dt);
	if (this->getState() == KOOPA_DEAD || this->getState() == KOOPA_STANDING) return;

	if (this->getIsStandOnSurface() == true) {
		this->setIsStandOnSurface(false);
	}

	this->animation->Update(_dt);

	if (this->getState() == KOOPA_MOVING_LEFT) {
		if (this->isOutOfFirstStage == false) {
			if (this->getIsGreenMode() == false && this->getX() + this->getVx() * _dt < this->leftAnchor) {
				this->setX(this->leftAnchor);
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}
		}

		this->plusXNoRound(this->getVx() * _dt);
	}
	else if (this->getState() == KOOPA_MOVING_RIGHT) {
		if (this->isOutOfFirstStage == false) {
			if (this->getIsGreenMode() == false && this->getX() + this->getBoundsWidth() + this->getVx() * _dt > this->rightAnchor) {
				this->setX(this->rightAnchor - this->getBoundsWidth());
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
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
			
			this->setIsShrinkageReverseMode(false);

			srand(time(NULL));

			int random = rand() % 2 + 1;
			if (random == 1) {
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}
			else {
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
		}
	}
	else if (this->getState() == KOOPA_FLYING_LEFT) {
		// vx now is < 0
		countFlyingX += (this->getVx() * _dt);
		float moreY = (-1 * (48 - (pow(countFlyingX + 24, 2) / 12)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX < -24) {
			this->setVy(abs(this->originVy));
		}
	}
	else if (this->getState() == KOOPA_FLYING_RIGHT) {
		// vx now is > 0
		countFlyingX += (this->getVx() * _dt);
		float moreY = (-1 * (48 - (pow(countFlyingX - 24, 2) / 12)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startFlyingY + moreY);

		if (countFlyingX > 24) {
			this->setVy(abs(this->originVy));
		}
	}
	else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE) {
		// vx now is < 0
		countThrownToShrinkageX += (this->getVx() * _dt);
		float moreY = (-1 * (72 - (pow(countThrownToShrinkageX + 12, 2) / 2)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startThrownToShrinkageY + moreY);

		if (countThrownToShrinkageX < -12) {
			this->setVy(abs(this->originVy));
		}
	}
	else if (this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
		// vx now is < 0
		countThrownToShrinkageX += (this->getVx() * _dt);
		float moreY = (-1 * (72 - (pow(countThrownToShrinkageX - 12, 2) / 2)));
		this->plusXNoRound(this->getVx() * _dt);
		this->setYNoRound(startThrownToShrinkageY + moreY);

		if (countThrownToShrinkageX > 12) {
			this->setVy(abs(this->originVy));
		}
	}
	else if (this->getState() == KOOPA_DROPPING_LEFT_FROM_AIR || this->getState() == KOOPA_DROPPING_RIGHT_FROM_AIR) {
		this->plusXNoRound(this->getVx()* _dt);
		this->plusYNoRound(this->getVy()* _dt);
	}
	else if (this->getState() == KOOPA_THROWN_LEFT_AWAY) {
		this->plusXNoRound(-2);
		this->setY(this->startThrownY + (-1 * (16 - (pow(thrownX + 24, 2) / 36)))); // -1: Oxy in game vs math
		thrownX -= (2);
	}
	else if (this->getState() == KOOPA_THROWN_RIGHT_AWAY) {
		this->plusXNoRound(2);
		this->setY(this->startThrownY + (-1 * (16 - (pow(thrownX - 24, 2) / 36)))); // -1: Oxy in game vs math
		thrownX += (2);
	}
}

void Koopa::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == KOOPA_DEAD) return;
	if (this->animation != NULL) {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), this->getIsFlip(), this->getIsShrinkageReverseMode(), D3DXVECTOR2(-4, -8));
	}

	if (Setting::getInstance()->getDebugMode()) {
		Drawing::getInstance()->drawDebugBox(this->animation->getCurrentBounds(), NULL, this->getPosition());
	}
}

void Koopa::handleHardComponentCollision(Component* _component, float _dt)
{
	if (this->getState() == KOOPA_THROWN_LEFT_AWAY || this->getState() == KOOPA_THROWN_RIGHT_AWAY) return;
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_component, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == bottomEdge) {
			this->setIsStandOnSurface(true);
			if (this->isOutOfFirstStage == true) {
				this->leftAnchor = _component->getX();
				this->rightAnchor = _component->getX() + _component->getWidth();
			}

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
			else if (this->getState() == KOOPA_FLYING_LEFT) {
				this->setState(KoopaState::KOOPA_FLYING_LEFT);
			}
			else if (this->getState() == KOOPA_FLYING_RIGHT) {
				this->setState(KoopaState::KOOPA_FLYING_RIGHT);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE || this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_SHRINKAGE);
			}
			else if (this->getState() == KOOPA_DROPPING_LEFT_FROM_AIR) {
				if (this->getIsFlyingMode()) {
					this->setState(KoopaState::KOOPA_FLYING_LEFT);
				}
				else { // KOOPA_THROWN_LEFT_TO_SHINKAGE
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				}
			}
			else if (this->getState() == KOOPA_DROPPING_RIGHT_FROM_AIR) {
				if (this->getIsFlyingMode()) {
					this->setState(KoopaState::KOOPA_FLYING_RIGHT);
				}
				else { // KOOPA_THROWN_RIGHT_TO_SHINKAGE
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
				}
			}

			this->setY(_component->getY() - this->getBoundsHeight());
		}
		else if (edge == topEdge) {
			if (this->getState() == KOOPA_FLYING_LEFT) {
				this->setState(KoopaState::KOOPA_DROPPING_LEFT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_FLYING_RIGHT) {
				this->setState(KoopaState::KOOPA_DROPPING_RIGHT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_DROPPING_LEFT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_DROPPING_RIGHT_FROM_AIR);
			}
		}
		else if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _component->getY()) {
			if (this->getState() == KOOPA_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE) {
				if (this->getVy() < 0) {
					this->setState(KoopaState::KOOPA_THROWN_RIGHT_TO_SHINKAGE);
				}
				else {
					this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
				}
			}
			this->plusX(get<1>(collisionResult)* this->getVx());
		}
		else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _component->getY()) {
			if (this->getState() == KOOPA_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
			}
			else if (this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				if (this->getVy() < 0) {
					this->setState(KoopaState::KOOPA_THROWN_LEFT_TO_SHINKAGE);
				}
				else {
					this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
				}
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
				if ((_component->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _component->getX() + _component->getWidth())
					|| (_component->getX() <= this->getX() && this->getX() <= _component->getX() + _component->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _component->getY()) {
						this->setIsStandOnSurface(true);
						if (this->isOutOfFirstStage == true) {
							this->leftAnchor = _component->getX();
							this->rightAnchor = _component->getX() + _component->getWidth();
						}
					}
				}
			}
		}
	}
}

void Koopa::handleGiftBrickCollision(GiftBrick* _giftBrick, Mario* _mario, float _dt)
{
	if (this->getState() == KOOPA_THROWN_LEFT_AWAY || this->getState() == KOOPA_THROWN_RIGHT_AWAY) return;
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_giftBrick, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == bottomEdge) {
			this->setIsStandOnSurface(true);

			if (this->isOutOfFirstStage == true) {
				this->leftAnchor = _giftBrick->getX();
				this->rightAnchor = _giftBrick->getX() + _giftBrick->getWidth();
			}

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
			else if (this->getState() == KOOPA_FLYING_LEFT) {
				this->setState(KoopaState::KOOPA_FLYING_LEFT);
			}
			else if (this->getState() == KOOPA_FLYING_RIGHT) {
				this->setState(KoopaState::KOOPA_FLYING_RIGHT);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE || this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_SHRINKAGE);
			}
			else if (this->getState() == KOOPA_DROPPING_LEFT_FROM_AIR) {
				if (this->getIsFlyingMode()) {
					this->setState(KoopaState::KOOPA_FLYING_LEFT);
				}
				else { // KOOPA_THROWN_LEFT_TO_SHINKAGE
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				}
			}
			else if (this->getState() == KOOPA_DROPPING_RIGHT_FROM_AIR) {
				if (this->getIsFlyingMode()) {
					this->setState(KoopaState::KOOPA_FLYING_RIGHT);
				}
				else { // KOOPA_THROWN_RIGHT_TO_SHINKAGE
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
				}
			}

			this->setY(_giftBrick->getY() - this->getBoundsHeight());
		}
		else if (edge == topEdge) {
			if (this->getState() == KOOPA_FLYING_LEFT) {
				this->setState(KoopaState::KOOPA_DROPPING_LEFT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_FLYING_RIGHT) {
				this->setState(KoopaState::KOOPA_DROPPING_RIGHT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_DROPPING_LEFT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_DROPPING_RIGHT_FROM_AIR);
			}

			if (_giftBrick->getState() == FULLGIFTBRICK) {
				if (_giftBrick->getGiftType() == SuperMushroomOrSuperLeaf) {
					if (_mario->getIsSuperMode() == false) {
						_giftBrick->setGiftType(GiftType::SuperMushroomGift);
					}
					else {
						_giftBrick->plusY(_mario->getVy() * _dt + (_giftBrick->getHeight() / 2));
						_giftBrick->setGiftType(GiftType::SuperLeafGift);
					}
				}

				if (_giftBrick->getGiftType() == GiftType::MultiCoinGift && _giftBrick->getIsPlayingPointAnimation()) {
					// Dont pop up
				}
				else {
					_giftBrick->setState(GiftBrickState::POPUPGIFTBRICK);

					if (_giftBrick->getGiftType() == Point100Gift || _giftBrick->getGiftType() == GiftType::MultiCoinGift) {
						ScoreBoard::getInstance()->plusCoin(1);
						ScoreBoard::getInstance()->plusPoint(100);
					}
				}
			}
		}
		else if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _giftBrick->getY() && this->getY() != _giftBrick->getY() + _giftBrick->getHeight()) {
			if (this->getState() == KOOPA_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE) {
				if (this->getVy() < 0) {
					this->setState(KoopaState::KOOPA_THROWN_RIGHT_TO_SHINKAGE);
				}
				else {
					this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
				}
			}
			this->plusX(get<1>(collisionResult) * this->getVx());

			if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT
				|| this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
				if (_giftBrick->getState() == FULLGIFTBRICK) {
					if (_giftBrick->getGiftType() == SuperMushroomOrSuperLeaf) {
						if (_mario->getIsSuperMode() == false) {
							_giftBrick->setGiftType(GiftType::SuperMushroomGift);
						}
						else {
							_giftBrick->plusY(_mario->getVy() * _dt + (_giftBrick->getHeight() / 2));
							_giftBrick->setGiftType(GiftType::SuperLeafGift);
						}
					}

					if (_giftBrick->getGiftType() == GiftType::MultiCoinGift && _giftBrick->getIsPlayingPointAnimation()) {
						// Dont pop up
					}
					else {
						_giftBrick->setState(GiftBrickState::POPUPGIFTBRICK);

						if (_giftBrick->getGiftType() == Point100Gift || _giftBrick->getGiftType() == GiftType::MultiCoinGift) {
							ScoreBoard::getInstance()->plusCoin(1);
							ScoreBoard::getInstance()->plusPoint(100);
						}
					}
				}
			}
		}
		else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _giftBrick->getY() && this->getY() != _giftBrick->getY() + _giftBrick->getHeight()) {
			if (this->getState() == KOOPA_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
			}
			else if (this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				if (this->getVy() < 0) {
					this->setState(KoopaState::KOOPA_THROWN_LEFT_TO_SHINKAGE);
				}
				else {
					this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
				}
			}
			this->plusX(get<1>(collisionResult) * this->getVx());

			if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT
				|| this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
				if (_giftBrick->getState() == FULLGIFTBRICK) {
					if (_giftBrick->getGiftType() == SuperMushroomOrSuperLeaf) {
						if (_mario->getIsSuperMode() == false) {
							_giftBrick->setGiftType(GiftType::SuperMushroomGift);
						}
						else {
							_giftBrick->plusY(_mario->getVy() * _dt + (_giftBrick->getHeight() / 2));
							_giftBrick->setGiftType(GiftType::SuperLeafGift);
						}
					}

					if (_giftBrick->getGiftType() == GiftType::MultiCoinGift && _giftBrick->getIsPlayingPointAnimation()) {
						// Dont pop up
					}
					else {
						_giftBrick->setState(GiftBrickState::POPUPGIFTBRICK);

						if (_giftBrick->getGiftType() == Point100Gift || _giftBrick->getGiftType() == GiftType::MultiCoinGift) {
							ScoreBoard::getInstance()->plusCoin(1);
							ScoreBoard::getInstance()->plusPoint(100);
						}
					}
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
				if ((_giftBrick->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _giftBrick->getX() + _giftBrick->getWidth())
					|| (_giftBrick->getX() <= this->getX() && this->getX() <= _giftBrick->getX() + _giftBrick->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _giftBrick->getY()) {
						this->setIsStandOnSurface(true);
						if (this->isOutOfFirstStage == true) {
							this->leftAnchor = _giftBrick->getX();
							this->rightAnchor = _giftBrick->getX() + _giftBrick->getWidth();
						}
					}
				}
			}
		}
	}
}

void Koopa::handleBlockCollision(Component* _block, float _dt)
{
	if (this->getState() == KOOPA_THROWN_LEFT_AWAY || this->getState() == KOOPA_THROWN_RIGHT_AWAY) return;

	//if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT || this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
		tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_block, _dt);
		if (get<0>(collisionResult) == true) {
			CollisionEdge edge = get<2>(collisionResult)[0];
			if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->isOutOfFirstStage == true) {
					this->leftAnchor = _block->getX();
					this->rightAnchor = _block->getX() + _block->getWidth();
				}

				if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
					this->plusYNoRound(this->getVy() * get<1>(collisionResult));
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				}
				else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
					this->plusYNoRound(this->getVy() * get<1>(collisionResult));
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
				}
				else if (this->getState() == KOOPA_FLYING_LEFT) {
					this->setState(KoopaState::KOOPA_FLYING_LEFT);
				}
				else if (this->getState() == KOOPA_FLYING_RIGHT) {
					this->setState(KoopaState::KOOPA_FLYING_RIGHT);
				}
				else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE || this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
					this->setState(KoopaState::KOOPA_SHRINKAGE);
				}
				else if (this->getState() == KOOPA_DROPPING_LEFT_FROM_AIR) {
					if (this->getIsFlyingMode()) {
						this->setState(KoopaState::KOOPA_FLYING_LEFT);
					}
					else { // KOOPA_THROWN_LEFT_TO_SHINKAGE
						this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
					}
				}
				else if (this->getState() == KOOPA_DROPPING_RIGHT_FROM_AIR) {
					if (this->getIsFlyingMode()) {
						this->setState(KoopaState::KOOPA_FLYING_RIGHT);
					}
					else { // KOOPA_THROWN_RIGHT_TO_SHINKAGE
						this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
					}
				}

				this->setY(_block->getY() - this->getBoundsHeight());
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
					if ((_block->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _block->getX() + _block->getWidth())
						|| (_block->getX() <= this->getX() && this->getX() <= _block->getX() + _block->getWidth())) { // this is check which ground that mario is standing on
						if (this->getY() + this->getBoundsHeight() == _block->getY()) {
							this->setIsStandOnSurface(true);
							if (this->isOutOfFirstStage == true) {
								this->leftAnchor = _block->getX();
								this->rightAnchor = _block->getX() + _block->getWidth();
							}
						}
					}
				}
			}
		}
	//}
}

void Koopa::handleGoombaCollision(Goomba* _goomba, float _dt)
{
	if (this->getState() == KOOPA_THROWN_LEFT_AWAY || this->getState() == KOOPA_THROWN_RIGHT_AWAY) return;

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
				/*|| this->getState() == KOOPA_DROPPING_LEFT
				|| this->getState() == KOOPA_DROPPING_RIGHT*/) {
				this->plusX(this->getVx() * get<1>(collisionResult));
				this->plusY(this->getVy() * get<1>(collisionResult));
				this->convertMovingState();

				_goomba->plusX(_goomba->getVx() * get<1>(collisionResult));
				_goomba->plusY(_goomba->getVy() * get<1>(collisionResult));
				_goomba->convertMovingState();
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT
				|| this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
				|| this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT
				|| this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
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
	if (this->getState() == KOOPA_THROWN_LEFT_AWAY || this->getState() == KOOPA_THROWN_RIGHT_AWAY) return;

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



	// When mario turning around
	if (_mario->getIsTurningAround()) {
		if (get<0>(_mario->sweptAABBByFrame(this, _dt)) || _mario->isCollidingByFrame(this->getFrame())) {
			if (_mario->getIsFlip()) { // <--
				if (this->getX() <= _mario->getX()
					&& this->getX() + this->getWidth() >= _mario->getX() - _mario->getLeftSpace()
					&& _mario->getBounds().top + _mario->getTailMarginTop() >= this->getY()
					&& _mario->getBounds().bottom - _mario->getTailMarginBottom() <= this->getY() + this->getHeight()) {
					if (this->getState() != KOOPA_THROWN_LEFT_TO_SHINKAGE) {
						this->setState(KoopaState::KOOPA_THROWN_LEFT_TO_SHINKAGE);

						AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), this->getX(), this->getY())));
						return;
					}
				}
			}
			else { // -->
				if (this->getX() >= _mario->getX()
					&& this->getX() <= _mario->getX() + _mario->getBoundsWidth() + _mario->getLeftSpace()
					&& _mario->getBounds().top + _mario->getTailMarginTop() >= this->getY()
					&& _mario->getBounds().bottom - _mario->getTailMarginBottom() <= this->getY() + this->getHeight()) {
					if (this->getState() != KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
						this->setState(KoopaState::KOOPA_THROWN_RIGHT_TO_SHINKAGE);

						AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), this->getX(), this->getY())));
						return;
					}
				}
			}
		}
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	/*if (this->getState() == KOOPA_FLYING_LEFT || this->getState() == KOOPA_FLYING_RIGHT || this->getState() == KOOPA_DROPPING_LEFT || this->getState() == KOOPA_DROPPING_RIGHT) {
		this->setVy(this->getStoredVy());
	}*/

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
				_mario->plusX(get<1>(collisionResult)* _mario->getVx());
				_mario->setState(MarioState::DIE);
			}
		}
		else if (edge == bottomEdge) {
			this->plusX(get<1>(collisionResult) * this->getVx());
			this->plusY(get<1>(collisionResult) * this->getVy());

			_mario->plusX(get<1>(collisionResult) * _mario->getVx());
			_mario->plusY(get<1>(collisionResult) * _mario->getVy());
			_mario->setState(MarioState::DIE);
		}
		else if (edge == topEdge && _mario->getState() == DROPPING) { // _mario->getState() == DROPPING: for prevenet conflict check collide from mario and from koopa
			//_mario->plusY(get<1>(collisionResult) * _mario->getVy() + this->getHeight() / 4);
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
			else if (this->getState() == KOOPA_FLYING_LEFT) {
				//this->plusY(2 * get<1>(collisionResult) * abs(_mario->getVy()));
				this->setState(KoopaState::KOOPA_DROPPING_LEFT);
			}
			else if (this->getState() == KOOPA_FLYING_RIGHT) {
				//this->plusY(2 * get<1>(collisionResult) * abs(_mario->getVy()));
				this->setState(KoopaState::KOOPA_DROPPING_RIGHT);
			}
			else {
				this->setState(KoopaState::KOOPA_SHRINKAGE);
			}
			
			this->setupPointAnimPosition();
		}
	}
	else if (this->isCollidingByBounds(_mario->getBounds())) {
		/*if ((_mario->getState() == WALKING || _mario->getState() == STANDING)
			&& this->getState() != KOOPA_SHRINKAGE
			&& this->getState() != KOOPA_SHRINKAGE_SHAKING
			&& this->getState() != KOOPA_FLYING_LEFT
			&& this->getState() != KOOPA_FLYING_RIGHT) {*/
			//_mario->plusX(get<1>(collisionResult) * _mario->getVx());
			_mario->setState(MarioState::DIE);
		/*}
		else if ((_mario->getState() == DROPPING)
			&& (this->getState() == KOOPA_FLYING_LEFT
				|| this->getState() == KOOPA_FLYING_RIGHT)) {

			if (abs(_mario->getBounds().left - this->getBounds().left) < 14) {
				if (this->getState() == KOOPA_FLYING_LEFT) {
					this->setState(KoopaState::KOOPA_DROPPING_LEFT);
				}
				else if (this->getState() == KOOPA_FLYING_RIGHT) {
					this->setState(KoopaState::KOOPA_DROPPING_RIGHT);
				}
				
				_mario->setState(MarioState::JUMPING);
			}
			else {
				this->plusX(2 * get<1>(collisionResult) * this->getVx());
				if (_mario->getIsSuperMode() == false) {
					this->setState(KoopaState::KOOPA_STANDING);
				}
				_mario->plusX(get<1>(collisionResult) * _mario->getVx());
				_mario->setState(MarioState::DIE);
			}
		}*/
	}
}

void Koopa::handleFireBallCollision(FireBall* _fireBall, float _dt)
{
	if (this->getState() == KOOPA_THROWN_LEFT_AWAY || this->getState() == KOOPA_THROWN_RIGHT_AWAY) return;
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_fireBall, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByFrame(_fireBall->getFrame())) {
		_fireBall->plusX(get<1>(collisionResult) * _fireBall->getVx());
		_fireBall->plusY(get<1>(collisionResult) * _fireBall->getVy());

		this->plusX(get<1>(collisionResult) * this->getVx());
		this->plusX(get<1>(collisionResult) * this->getVx());

		if (_fireBall->getState() == FIREBALL_FLYING_LEFT) {
			this->setState(KoopaState::KOOPA_THROWN_LEFT_AWAY);
		}
		else if (_fireBall->getState() == FIREBALL_FLYING_RIGHT) {
			this->setState(KoopaState::KOOPA_THROWN_RIGHT_AWAY);
		}

		_fireBall->setState(FireBallState::FIREBALL_DISAPPEARED);
		ScoreBoard::getInstance()->plusPoint(2 * this->getDefaultPoint());
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(2 * this->getDefaultPoint(), this->getX(), this->getY())));
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), _fireBall->getX(), _fireBall->getY())));
	}
}

void Koopa::handleGoldenBrickCollision(GoldenBrick* _goldenBrick, float _dt)
{
	if (_goldenBrick->getState() == GOLDEN_BRICK_BEING_COIN || _goldenBrick->getState() == GOLDEN_BRICK_DISAPPEARING || _goldenBrick->getState() == GOLDEN_BRICK_DEAD) return;
	if (this->getState() == KOOPA_THROWN_LEFT_AWAY || this->getState() == KOOPA_THROWN_RIGHT_AWAY) return;
	
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_goldenBrick, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == bottomEdge) {
			this->setIsStandOnSurface(true);
			if (this->isOutOfFirstStage == true) {
				this->leftAnchor = _goldenBrick->getX();
				this->rightAnchor = _goldenBrick->getX() + _goldenBrick->getWidth();
			}


			this->setY(_goldenBrick->getY() - this->getBoundsHeight());

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
			else if (this->getState() == KOOPA_FLYING_LEFT) {
				this->setState(KoopaState::KOOPA_FLYING_LEFT);
			}
			else if (this->getState() == KOOPA_FLYING_RIGHT) {
				this->setState(KoopaState::KOOPA_FLYING_RIGHT);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE || this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_SHRINKAGE);
			}
			else if (this->getState() == KOOPA_DROPPING_LEFT_FROM_AIR) {
				if (this->getIsFlyingMode()) {
					this->setState(KoopaState::KOOPA_FLYING_LEFT);
				}
				else { // KOOPA_THROWN_LEFT_TO_SHINKAGE
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				}
			}
			else if (this->getState() == KOOPA_DROPPING_RIGHT_FROM_AIR) {
				if (this->getIsFlyingMode()) {
					this->setState(KoopaState::KOOPA_FLYING_RIGHT);
				}
				else { // KOOPA_THROWN_RIGHT_TO_SHINKAGE
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
				}
			}
		}
		else if (edge == topEdge) {
			if (this->getState() == KOOPA_FLYING_LEFT) {
				this->setState(KoopaState::KOOPA_DROPPING_LEFT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_FLYING_RIGHT) {
				this->setState(KoopaState::KOOPA_DROPPING_RIGHT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_DROPPING_LEFT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_DROPPING_RIGHT_FROM_AIR);
			}
		}
		else if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _goldenBrick->getY() && this->getY() != _goldenBrick->getY() + _goldenBrick->getHeight()) {
			if (this->getState() == KOOPA_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE) {
				if (this->getVy() < 0) {
					this->setState(KoopaState::KOOPA_THROWN_RIGHT_TO_SHINKAGE);
				}
				else {
					this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
				}
			}
			this->plusX(get<1>(collisionResult) * this->getVx());

			if (_goldenBrick->getState() == GOLDEN_BRICK_STAYING
				&& (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT || this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT || this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT || this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT)) {
				_goldenBrick->setState(GoldenBrickState::GOLDEN_BRICK_DISAPPEARING);
			}
		}
		else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _goldenBrick->getY() && this->getY() != _goldenBrick->getY() + _goldenBrick->getHeight()) {
			if (this->getState() == KOOPA_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				if (this->getVy() < 0) {
					this->setState(KoopaState::KOOPA_THROWN_LEFT_TO_SHINKAGE);
				}
				else {
					this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
				}
			}
			this->plusX(get<1>(collisionResult) * this->getVx());

			if (_goldenBrick->getState() == GOLDEN_BRICK_STAYING
				&& (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT || this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT || this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT || this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT)) {
				_goldenBrick->setState(GoldenBrickState::GOLDEN_BRICK_DISAPPEARING);
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
				if ((_goldenBrick->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _goldenBrick->getX() + _goldenBrick->getWidth())
					|| (_goldenBrick->getX() <= this->getX() && this->getX() <= _goldenBrick->getX() + _goldenBrick->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _goldenBrick->getY()) {
						this->setIsStandOnSurface(true);
						if (this->isOutOfFirstStage == true) {
							this->leftAnchor = _goldenBrick->getX();
							this->rightAnchor = _goldenBrick->getX() + _goldenBrick->getWidth();
						}
					}
				}
			}
		}
	}
}

void Koopa::handleKoopaCollision(Koopa* _koopa, float _dt)
{
	if (this->getState() == KOOPA_THROWN_LEFT_AWAY || this->getState() == KOOPA_THROWN_RIGHT_AWAY) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_koopa, _dt);
	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_koopa->getBounds())) {
		if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT || this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
			_koopa->plusX(get<1>(collisionResult) * _koopa->getVx());
			_koopa->plusY(get<1>(collisionResult) * _koopa->getVy());

			this->plusX(get<1>(collisionResult) * this->getVx());
			this->plusX(get<1>(collisionResult) * this->getVx());

			ScoreBoard::getInstance()->plusPoint(2 * _koopa->getDefaultPoint());
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(2 * _koopa->getDefaultPoint(), _koopa->getX(), _koopa->getY())));
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), _koopa->getX(), _koopa->getY())));

			_koopa->setState(KoopaState::KOOPA_THROWN_LEFT_AWAY);
		}
		else if (this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT || this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
			_koopa->plusX(get<1>(collisionResult) * _koopa->getVx());
			_koopa->plusY(get<1>(collisionResult) * _koopa->getVy());

			this->plusX(get<1>(collisionResult) * this->getVx());
			this->plusX(get<1>(collisionResult) * this->getVx());

			ScoreBoard::getInstance()->plusPoint(2 * _koopa->getDefaultPoint());
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(2 * _koopa->getDefaultPoint(), _koopa->getX(), _koopa->getY())));
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), _koopa->getX(), _koopa->getY())));

			_koopa->setState(KoopaState::KOOPA_THROWN_RIGHT_AWAY);
		}
	}
}

void Koopa::handleMusicBoxCollision(MusicBox* _musicBox, float _dt)
{
	if (this->getState() == KOOPA_THROWN_LEFT_AWAY || this->getState() == KOOPA_THROWN_RIGHT_AWAY) return;

	if (_musicBox->getIsSpecial() && _musicBox->getIsTransparentMode()) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_musicBox, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == bottomEdge) {
			this->setIsStandOnSurface(true);
			if (this->isOutOfFirstStage == true) {
				this->leftAnchor = _musicBox->getX();
				this->rightAnchor = _musicBox->getX() + _musicBox->getWidth();
			}

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
			else if (this->getState() == KOOPA_FLYING_LEFT) {
				this->setState(KoopaState::KOOPA_FLYING_LEFT);
			}
			else if (this->getState() == KOOPA_FLYING_RIGHT) {
				this->setState(KoopaState::KOOPA_FLYING_RIGHT);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE || this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_SHRINKAGE);
			}
			else if (this->getState() == KOOPA_DROPPING_LEFT_FROM_AIR) {
				if (this->getIsFlyingMode()) {
					this->setState(KoopaState::KOOPA_FLYING_LEFT);
				}
				else { // KOOPA_THROWN_LEFT_TO_SHINKAGE
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				}
			}
			else if (this->getState() == KOOPA_DROPPING_RIGHT_FROM_AIR) {
				if (this->getIsFlyingMode()) {
					this->setState(KoopaState::KOOPA_FLYING_RIGHT);
				}
				else { // KOOPA_THROWN_RIGHT_TO_SHINKAGE
					this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
				}
			}

			this->setY(_musicBox->getY() - this->getBoundsHeight());
		}
		else if (edge == topEdge) {
			if (this->getState() == KOOPA_FLYING_LEFT) {
				this->setState(KoopaState::KOOPA_DROPPING_LEFT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_FLYING_RIGHT) {
				this->setState(KoopaState::KOOPA_DROPPING_RIGHT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_DROPPING_LEFT_FROM_AIR);
			}
			else if (this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				this->setState(KoopaState::KOOPA_DROPPING_RIGHT_FROM_AIR);
			}

			_musicBox->setState(MusicBoxState::MUSIC_BOX_JUMPING_UP);
		}
		else if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _musicBox->getY() && this->getY() != _musicBox->getY() + _musicBox->getHeight()) {
			if (this->getState() == KOOPA_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_LEFT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
			}
			else if (this->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE) {
				if (this->getVy() < 0) {
					this->setState(KoopaState::KOOPA_THROWN_RIGHT_TO_SHINKAGE);
				}
				else {
					this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
				}
			}
			this->plusX(get<1>(collisionResult) * this->getVx());
			_musicBox->setState(MusicBoxState::MUSIC_BOX_JUMPING_UP);
		}
		else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _musicBox->getY() && this->getY() != _musicBox->getY() + _musicBox->getHeight()) {
			if (this->getState() == KOOPA_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
			}
			else if (this->getState() == KOOPA_SHRINKAGE_DROPPING_RIGHT) {
				this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
			}
			else if (this->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				if (this->getVy() < 0) {
					this->setState(KoopaState::KOOPA_THROWN_LEFT_TO_SHINKAGE);
				}
				else {
					this->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
				}
			}
			this->plusX(get<1>(collisionResult) * this->getVx());
			_musicBox->setState(MusicBoxState::MUSIC_BOX_JUMPING_UP);
		}
	}
	else {
		// if supermushroom walk out of ground's top surface, it will drop
		if (this->getState() == KOOPA_SHRINKAGE_MOVING_LEFT
			|| this->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT
			|| this->getState() == KOOPA_MOVING_LEFT
			|| this->getState() == KOOPA_MOVING_RIGHT) {
			if (this->getIsStandOnSurface() == false) {
				if ((_musicBox->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _musicBox->getX() + _musicBox->getWidth())
					|| (_musicBox->getX() <= this->getX() && this->getX() <= _musicBox->getX() + _musicBox->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _musicBox->getY()) {
						this->setIsStandOnSurface(true);
						if (this->isOutOfFirstStage == true) {
							this->leftAnchor = _musicBox->getX();
							this->rightAnchor = _musicBox->getX() + _musicBox->getWidth();
						}
					}
				}
			}
		}
	}
}
