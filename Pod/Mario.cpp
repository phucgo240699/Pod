#include "Mario.h"

Mario::Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY)
{
	MainCharacter::MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY);

	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
}

Mario::Mario(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : MainCharacter(_position, _vx, _vy, _limitX, _limitY)
{
	MainCharacter::MainCharacter(_position, _vx, _vy, _limitX, _limitY);

	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
}

Animation* Mario::getCurrentAnimation()
{
	return this->currentAnimation;
}

Animation* Mario::getPressureAnimation()
{
	return this->pressureAnimation;
}

MarioSubState Mario::getSubState()
{
	return this->subState;
}

FireBall* Mario::getFirstFireBall()
{
	return this->firstFireBall;
}

MarioState Mario::getState()
{
	return this->state;
}

MarioState Mario::getPressureState()
{
	return this->pressureState;
}

RECT Mario::getBounds()
{
	RECT r = RECT();
	r.top = this->getY();
	r.bottom = r.top + this->getBoundsHeight();
	r.left = this->getX();
	r.right = r.left + this->getBoundsWidth();

	return r;
}

bool Mario::getIsFlip()
{
	return this->isFlip;
}

bool Mario::getIsConverting()
{
	return this->isConverting;
}

bool Mario::getIsReduceWalking()
{
	return this->isReduceWalking;
}

float Mario::getBoundsWidth()
{
	return this->currentAnimation->getCurrentBoundsWidth();
}

float Mario::getBoundsHeight()
{
	return this->currentAnimation->getCurrentBoundsHeight();
}

float Mario::getWidth()
{
	return this->currentAnimation->getCurrentFrameWidth();
}

float Mario::getHeight()
{
	return this->currentAnimation->getCurrentFrameHeight() - Setting::getInstance()->getCollisionSafeSpace();
}

bool Mario::getIsStandOnSurface()
{
	return this->isStandOnSurface;
}

bool Mario::getIsSuperMode()
{
	return this->isSuperMode;
}

int Mario::getPointCoef()
{
	return this->pointCoef;
}

int Mario::getLeftSpace()
{
	return this->leftSpace;
}

int Mario::getTopSpace()
{
	return this->topSpace;
}

int Mario::getRightSpace()
{
	return this->rightSpace;
}

int Mario::getMarioLeftSpace()
{
	return this->marioLeftSpace;
}

int Mario::getMarioTopSpace()
{
	return this->marioTopSpace;
}

int Mario::getMarioRightSpace()
{
	return this->marioRightSpace;
}

int Mario::getSuperMarioLeftSpace()
{
	return this->superMarioLeftSpace;
}

int Mario::getSuperMarioTopSpace()
{
	return this->superMarioTopSpace;
}

int Mario::getSuperMarioRightSpace()
{
	return this->superMarioRightSpace;
}

int Mario::getSuperMarioFlyingLeftSpace()
{
	return this->superMarioFlyingLeftSpace;
}

int Mario::getSuperMarioFlyingTopSpace()
{
	return this->superMarioFlyingTopSpace;
}

int Mario::getSuperMarioFlyingRightSpace()
{
	return this->superMarioFlyingRightSpace;
}

int Mario::getMomentumToFly()
{
	return this->momentumToFly;
}

int Mario::getMomentumLevelToFly()
{
	return this->momentumLevelToFly;
}

bool Mario::getIsFlashMode()
{
	return this->isFlashMode;
}

bool Mario::getIsFireMode()
{
	return this->isFireMode;
}

bool Mario::getIsCloudMode()
{
	return this->isCloudMode;
}

bool Mario::getIsFlyingMode()
{
	return this->isFlyingMode;
}

bool Mario::getIsPreFlyingUpMode()
{
	return this->isPreFlyingUpMode;
}

bool Mario::getIsFlyingUpMode()
{
	return this->isFlyingUpMode;
}

bool Mario::getIsTurningAround()
{
	return this->isTurningAround;
}

bool Mario::getIsPressA()
{
	return this->isPressA;
}

void Mario::loadInfo(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);
	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setLimitX(stof(v[2]));
	this->setLimitY(stof(v[3]));
	this->setLeftSpace(stof(v[4]));
	this->setTopSpace(stof(v[5]));
	this->setRightSpace(stof(v[6]));
	this->setMarioLeftSpace(stof(v[7]));
	this->setMarioTopSpace(stof(v[8]));
	this->setMarioRightSpace(stof(v[9]));
	this->setSuperMarioLeftSpace(stof(v[10]));
	this->setSuperMarioTopSpace(stof(v[11]));
	this->setSuperMarioRightSpace(stof(v[12]));
	this->setSuperMarioFlyingLeftSpace(stof(v[13]));
	this->setSuperMarioFlyingTopSpace(stof(v[14]));
	this->setSuperMarioFlyingRightSpace(stof(v[15]));
	//this->setState(Tool::getMarioStateFromString(v[4]));

	this->firstFireBall = new FireBall(0, 0, stof(v[16]), stof(v[17]), 0, 0, stoi(v[18]));
}

void Mario::setIsFlip(bool _isFlip)
{
	this->isFlip = _isFlip;
}

void Mario::setIsConverting(bool _isConverting)
{
	this->isConverting = _isConverting;
}

void Mario::setFirstFireBallAnimation(Animation* _animation)
{
	this->firstFireBall->setAnimation(_animation);
}

void Mario::setState(MarioState _state)
{
 	if (currentAnimation != NULL) {
		this->oldFrameWidth = this->currentAnimation->getCurrentBoundsWidth();
		this->oldFrameHeight = this->currentAnimation->getCurrentBoundsHeight();
	}
	
	if (this->getState() == TRANSFERING_TO_FLY) {
		this->toggleFlyingMode();
	}

	switch (_state)
	{
	case STANDING:
	{
		this->setIsFlyingUpMode(false);
		this->setIsReduceWalking(false);
		this->resetPointCoef();
		if (this->getState() != STANDING || this->currentAnimation == NULL) {
			if (this->getVx() != 0 && this->getState() == DROPPING) {
				this->setState(MarioState::WALKING);
				return;
			}
			delete currentAnimation;

			if (this->getIsFlyingMode()) {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireStanding());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingStanding());
				}
			}
			else if (this->getIsSuperMode()) {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireStanding());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioStanding());
				}
			}
			else {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireStanding());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioStanding());
				}
			}

			this->setTargetVx(0);
			this->setTargetVy(0);
			this->setAccelerationY(0);
			this->setVy(0);

			this->setAccelerationX(0);
			this->setVx(0);
		}
		break;
	}

	case WALKING:
	{
		delete currentAnimation;

		this->setIsFlyingUpMode(false);
		if (this->getIsFlyingMode()) {
			if (this->getIsConverting()) {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireConverting());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingConverting());
				}
			}
			else {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireWalking());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingWalking());
				}
			}
		}
		else if (this->getIsSuperMode()) {
			if (this->getIsConverting()) {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireConverting());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioConverting());
				}
			}
			else {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireWalking());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioWalking());
				}
			}
		}
		else {
			if (this->getIsConverting()) {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireConverting());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioConverting());
				}
			}
			else {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireWalking());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioWalking());
				}
			}
		}
		this->setVy(0);
		this->setTargetVy(0);
		this->setAccelerationY(0);
		break;
	}

	case JUMPING:
	{
		if (this->getState() != DROPPING || this->getIsFlyingUpMode()) {
			delete currentAnimation;
			
			if (this->getIsFlyingUpMode()) {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireFlyingUp());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingUp());
				}
			}
			else if (this->getIsFlyingMode()) {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireJumping());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingJumping());
				}
			}
			else if (this->getIsSuperMode()) {
					if (this->getIsFireMode()) {
						this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireJumping());
					}
					else {
						this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioJumping());
					}
				}
			else {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireJumping());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioJumping());
				}
			}
		}
		this->setTargetVy(0);
		this->setVy(this->getIsSuperMode() ? -4.4 : -4.0);
		this->setAccelerationY(0.11);
		break;
	}

	case DROPPING:
	{
		if (this->getState() != JUMPING) {
			delete currentAnimation;
			if (this->getIsFlyingMode()) {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireDropping());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingDropping());
				}
			}
			else if (this->getIsSuperMode()) {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireDropping());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioDropping());
				}
			}
			else {
				if (this->getIsFireMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireDropping());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDropping());
				}
			}
		}
		this->setTargetVy(6);
		this->setAccelerationY(0.25);
		break;
	}

	case DIE:
	{
		if (this->getIsFlyingMode()) {
			this->setState(MarioState::TRANSFERING_TO_FLY);
			return;
		}
		else if (this->getIsSuperMode()) {
			this->setState(MarioState::SCALING_DOWN);
			return;
		}

		delete currentAnimation;
		if (this->getIsFireMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireDie());
		}
		else {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDie());
		}

		this->turnOffFireSkin(_state);
		this->setTargetVx(0);
		this->setTargetVy(0);
		this->setAccelerationX(0);
		this->setAccelerationY(0);
		this->setVx(0);
		this->setVy(0);
		break;
	}

	case DIE_JUMPING:
	{
		this->setTargetVx(0);
		this->setTargetVy(0);
		this->setAccelerationX(0);
		this->setAccelerationY(0.11);
		this->setVx(0);
		this->setVy(-4.4);
		break;
	}

	case DIE_DROPPING:
	{
		this->setTargetVx(0);
		this->setTargetVy(6);
		this->setAccelerationX(0);
		this->setAccelerationY(0.34);
		this->setVx(0);
		this->setVy(0);
		break;
	}

	case SCALING_UP:
	{
		delete currentAnimation;
		// Store old state to pressureState variable
		this->setIsSuperMode(true);
		this->setPressureState(MarioState(this->getState()));

		if (this->getIsFireMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireScalingUp());
		}
		else {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioScalingUp());
		}

		this->setTargetVx(0);
		this->setTargetVy(0);
		this->setAccelerationX(0);
		this->setAccelerationY(0);
		this->setVx(0);
		this->setVy(0);
		break;
	}

	case SCALING_DOWN:
	{
		this->setIsFlashMode(true);
		this->setIsFlyingUpMode(false);

		// Store old state to pressureState variable
		this->setPressureState(MarioState(this->getState()));

		this->setIsSuperMode(false);

		delete currentAnimation;
		if (this->getIsFireMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireScalingDown());
		}
		else {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioScalingDown());
		}

		this->countDownFlash = 120;

		this->setTargetVx(0);
		this->setTargetVy(0);
		this->setAccelerationX(0);
		this->setAccelerationY(0);
		this->setVx(0);
		this->setVy(0);
		break;
	}

	case TRANSFERING_TO_FLY:
	{
		delete currentAnimation;

		this->setIsPreFlyingUpMode(false);
		this->setIsFlyingUpMode(false);
		// Store old state to pressureState variable
		this->setPressureState(MarioState(this->getState()));

		this->currentAnimation = new Animation(AnimationBundle::getInstance()->getCloudEffect());

		this->setTargetVx(0);
		this->setTargetVy(0);
		this->setAccelerationX(0);
		this->setAccelerationY(0);
		this->setVx(0);
		this->setVy(0);
		break;
	}

	default:
		break;
	}


	// Change position when frame anim size change
	this->newFrameWidth = this->currentAnimation->getCurrentBoundsWidth();
	this->newFrameHeight = this->currentAnimation->getCurrentBoundsHeight();

	if (oldFrameWidth != newFrameWidth) {
		this->plusX(oldFrameWidth - newFrameWidth);
	}
	if (oldFrameHeight != newFrameHeight) {
		this->plusY(oldFrameHeight - newFrameHeight);
	}

	if (_state == SCALING_UP) {
		this->plusY(-1);
	}

	// Space between bounds and frame
	if (this->getState() == SCALING_DOWN) {
		this->setLeftSpace(this->getMarioLeftSpace());
		this->setTopSpace(this->getMarioTopSpace());
		this->setRightSpace(this->getMarioRightSpace());
	}
	else if (this->getState() == SCALING_UP) {
		this->setLeftSpace(this->getSuperMarioLeftSpace());
		this->setTopSpace(this->getSuperMarioTopSpace());
		this->setRightSpace(this->getSuperMarioRightSpace());
	}
	else if (this->getState() == TRANSFERING_TO_FLY) {
		if (this->getIsFlyingMode()) {
			this->setLeftSpace(this->getSuperMarioFlyingLeftSpace());
			this->setTopSpace(this->getSuperMarioFlyingTopSpace());
			this->setRightSpace(this->getSuperMarioFlyingRightSpace());
		}
		else {
			this->setLeftSpace(this->getSuperMarioLeftSpace());
			this->setTopSpace(this->getSuperMarioTopSpace());
			this->setRightSpace(this->getSuperMarioRightSpace());
		}
	}

	this->state = _state;
}

void Mario::setPressureState(MarioState _pressureState)
{
	this->pressureState = _pressureState;
}

void Mario::setPressureAnimation(Animation _animation)
{
	this->pressureAnimation = new Animation(_animation);
}

void Mario::setSubState(MarioSubState _subState)
{
	switch (_subState)
	{
	case NONE:
		break;
	case PUSHING:
		this->setVx(0);
		this->setAccelerationX(0);
		break;
	default:
		break;
	}
	this->subState = _subState;
}

void Mario::setIsStandOnSurface(bool _isStandOnSurface)
{
	this->isStandOnSurface = _isStandOnSurface;
}

void Mario::setupReduceWalking(bool _isReduceWalking)
{
	this->setIsReduceWalking(_isReduceWalking);
	if (this->getVx() < 0) {
		this->setAccelerationX(0.1);
	}
	else if (this->getVx() > 0) {
		this->setAccelerationX(-0.1);
	}
	if (this->getTargetVx() != 0) {
		this->setTargetVx(0);
	}
}

void Mario::setIsReduceWalking(bool _isReduceWalking)
{
	this->isReduceWalking = _isReduceWalking;
}

void Mario::setIsSuperMode(bool _isSuperMode)
{
	this->isSuperMode = _isSuperMode;
}

void Mario::setIsFlashMode(bool _isFlashMode)
{
	this->isFlashMode = _isFlashMode;
}

void Mario::turnOnFireSkin(MarioState _state)
{
	this->setIsFireMode(true);
	switch (_state)
	{
	case STANDING:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireStanding());
		}
		else if (this->getIsSuperMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireStanding());
		}
		else {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireStanding());
		}
		break;
	}

	case WALKING:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			if (this->getIsConverting()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireConverting());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireWalking());
			}
		}
		else if (this->getIsSuperMode()) {
			if (this->getIsConverting()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireConverting());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireWalking());
			}
		}
		else {
			if (this->getIsConverting()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireConverting());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireWalking());
			}
		}
		break;
	}

	case JUMPING:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireJumping());
		}
		else if (this->getIsSuperMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireJumping());
		}
		else {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireJumping());
		}
		break;
	}

	case DROPPING:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireDropping());
		}
		else if (this->getIsSuperMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireDropping());
		}
		else {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireDropping());
		}
		break;
	}

	case DIE:
	case DIE_DROPPING:
	case DIE_JUMPING:
	{
		this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireDie());
		break;
	}

	default:
		break;
	}
}

void Mario::turnOffFireSkin(MarioState _state)
{
	this->setIsFireMode(false);
	switch (_state)
	{
	case STANDING:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingStanding());
		}
		else if (this->getIsSuperMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioStanding());
		}
		else {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioStanding());
		}
		break;
	}

	case WALKING:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			if (this->getIsConverting()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingConverting());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingWalking());
			}
		}
		else if (this->getIsSuperMode()) {
			if (this->getIsConverting()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioConverting());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioWalking());
			}
		}
		else {
			if (this->getIsConverting()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioConverting());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioWalking());
			}
		}
		break;
	}

	case JUMPING:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingJumping());
		}
		else if (this->getIsSuperMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioJumping());
		}
		else {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioJumping());
		}
		break;
	}

	case DROPPING:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingDropping());
		}
		else if (this->getIsSuperMode()) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioDropping());
		}
		else {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDropping());
		}
		break;
	}

	case DIE:
	case DIE_DROPPING:
	case DIE_JUMPING:
	{
		this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDie());
		break;
	}

	default:
		break;
	}
}

void Mario::setIsFireMode(bool _isFireMode)
{
	this->isFireMode = _isFireMode;
}

void Mario::setIsCloudMode(bool _isCloudMode)
{
	this->isCloudMode = _isCloudMode;
}

void Mario::setIsFlyingMode(bool _isFlyingMode)
{
	this->isFlyingMode = _isFlyingMode;
}

void Mario::toggleFlyingMode()
{
	this->isFlyingMode = !(this->isFlyingMode);
}

void Mario::setIsTurningAround(bool _isTurningAround)
{
	this->isTurningAround = _isTurningAround;
}

void Mario::setIsPressA(bool _isPressA)
{
	this->isPressA = _isPressA;
}

void Mario::turnOnTurningAroundSkin()
{
	this->setPressureState(MarioState(this->getState()));
	if (this->getIsFireMode()) {
		this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireTurningAround());
	}
	else {
		this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingTurningAround());
	}
}

void Mario::turnOffTurningAroundSkin()
{
	this->setState(this->getPressureState());
}

void Mario::turnOnPreFlyingUpSkin()
{
	this->setPressureState(MarioState(this->getState()));
	if (this->getIsFireMode()) {
		this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFirePreFlyingUp());
	}
	else {
		this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioPreFlyingUp());
	}
}

void Mario::turnOffPreFlyingUpSkin()
{
	this->setState(this->getPressureState());
}

void Mario::setIsPreFlyingUpMode(bool _isPreFlyingUpMode)
{
	this->isPreFlyingUpMode = _isPreFlyingUpMode;
}

void Mario::setIsFlyingUpMode(bool _isFlyingUpMode)
{
	this->isFlyingUpMode = _isFlyingUpMode;
	if (_isFlyingUpMode == false) {
		this->setIsPreFlyingUpMode(false);
	}
}

void Mario::Update(float _dt)
{
	if (currentAnimation == NULL) {
		return;
	}

	if (this->getIsTurningAround()) {
		if (this->currentAnimation->getCurrentIndexFrame() >= this->currentAnimation->getTotalFrames() - 1
			&& this->currentAnimation->getAnimCount() >= this->currentAnimation->getAnimDelay()) {
			this->setIsTurningAround(false);
			this->turnOffTurningAroundSkin();
		}
	}
	if (this->getIsPressA()) {
		if (this->getState() == WALKING) {
			this->plusMomentum(1);
			if (this->getIsTurningAround() == false) {
				if (this->getMomentumLevelToFly() >= 7) {
					if (this->getIsPreFlyingUpMode() == false) {
						this->setIsPreFlyingUpMode(true);
						if (this->getIsPreFlyingUpMode()) {
							this->turnOnPreFlyingUpSkin();
						}
						else {
							this->turnOffPreFlyingUpSkin();
						}
					}
				}
				this->currentAnimation->Update(_dt);
			}
		}
	}

	// Update animation frame
	this->currentAnimation->Update(_dt);

	if (this->getState() == SCALING_UP) {
		if (this->currentAnimation->getCurrentIndexFrame() == this->currentAnimation->getTotalFrames() - 1
			&& this->currentAnimation->getAnimCount() >= this->currentAnimation->getAnimDelay()) {
			this->setState(this->getPressureState());
		}
	}

	else if (this->getState() == SCALING_DOWN) {
		if (this->currentAnimation->getCurrentIndexFrame() == this->currentAnimation->getTotalFrames() - 1
			&& this->currentAnimation->getAnimCount() >= this->currentAnimation->getAnimDelay()) {
			this->setState(this->getPressureState());
			//this->countDownFlash = this->getCurrentAnimation()->getTotalFrames() * 16;
		}
		this->countDownFlash -= 1;
	}

	else if (this->getIsFlashMode()) {
		this->countDownFlash -= 1;
		if (this->countDownFlash <= 0) {
			this->setIsFlashMode(false);
			this->countDownFlash = 0;
			//this->countDownFlash = this->getCurrentAnimation()->getTotalFrames() * 16;
		}
	}

	else if (this->getState() == TRANSFERING_TO_FLY) {
		if (this->currentAnimation->getCurrentIndexFrame() >= this->currentAnimation->getTotalFrames() - 1
			&& this->currentAnimation->getAnimCount() >= this->currentAnimation->getAnimDelay()) {
			this->setState(this->getPressureState());
		}
	}

	// Change from DIE to DIE_JUMPING
	else if (this->getState() == DIE) {
		if (this->currentAnimation->getCurrentIndexFrame() == this->currentAnimation->getTotalFrames() - 1
			&& this->currentAnimation->getAnimCount() >= this->currentAnimation->getAnimDelay()) {
			this->setState(MarioState::DIE_JUMPING);
		}
	}

	// Update position, velocity
	this->updateVelocity();
	if (this->getX() + round(this->getVx() * _dt) >= 0
		&& this->getX() + this->getBoundsWidth() + round(this->getVx() * _dt) <= this->getLimitX()
		&& this->getSubState() != PUSHING) {
		this->plusX(this->getVx() * _dt);
	}
	this->plusY(this->getVy() * _dt);

	// Navigate to WorldVC when Mario drop out of map to far
	if (this->getY() >= this->getLimitY() + 200) {
		this->setIsSuperMode(false);
		this->setIsFlyingMode(false);
		this->setIsPreFlyingUpMode(false);
		this->setIsFlyingUpMode(false);
		Setting::getInstance()->setIsTransfering(true);
		Setting::getInstance()->setSceneName(SceneName::WorldScene);
		ScoreBoard::getInstance()->minusMarioLife();
	}
}

void Mario::Draw()
{
	if (currentAnimation == NULL) {
		return;
	}
	Camera* camera = Camera::getInstance();
	float translateX = 0;
	if (this->getX() > camera->getWidth() / 2) {
		translateX = -camera->getX();
	}

	float translateY = 0;
	if (this->getY() > camera->getHeight() / 2) {
		translateY = -(camera->getY());
	}

	// Draw mario
	if (this->getIsFlashMode()) {
		this->currentAnimation->DrawMarioWithoutCamera(this->texture, this->getPosition(), D3DXVECTOR2(translateX, translateY), this->getLeftSpace(), this->getTopSpace(), this->getRightSpace(), this->getIsFlip(), (this->countDownFlash % 4 == 0 ? D3DCOLOR_ARGB(128, 255, 255, 255) : D3DCOLOR_XRGB(255, 255, 255)));
		//this->currentAnimation->DrawWithoutCamera(this->texture, this->getPosition(), D3DXVECTOR2(translateX - transX, translateY - this->getTopSpace()), this->getIsFlip(), (this->countDownFlash % 4 == 0 ? D3DCOLOR_ARGB(128, 255, 255, 255) : D3DCOLOR_XRGB(255, 255, 255)));
	}
	else if (this->getState() == SCALING_UP) {
		this->currentAnimation->DrawWithoutCamera(this->texture, this->getPosition(), D3DXVECTOR2(translateX, translateY), this->getIsFlip());
	}
	else {
		this->currentAnimation->DrawMarioWithoutCamera(this->texture, this->getPosition(), D3DXVECTOR2(translateX, translateY), this->getLeftSpace(), this->getTopSpace(), this->getRightSpace(), this->getIsFlip());
		//this->currentAnimation->DrawWithoutCamera(this->texture, this->getPosition(), D3DXVECTOR2(translateX - transX, translateY - this->getTopSpace()), this->getIsFlip(), D3DCOLOR_XRGB(255, 255, 255));
	}

	// Draw debug box
	if (debugMode == Setting::getInstance()->getDebugMode()) {
		Drawing::getInstance()->drawDebugBox(this->getBounds(), NULL, this->getPosition(), D3DXVECTOR2(translateX, translateY), false, D3DCOLOR_ARGB(128, 255, 255, 255));
	}
}

void Mario::updateVelocity()
{
	if (this->getTargetVx() > 0) {
		if (this->getVx() + this->getAccelerationX() <= this->getTargetVx()) {
			this->plusVx(this->getAccelerationX());
		}
		/*else {
			this->setVx(this->getTargetVx());
		}*/

		// Stop Converting
		if (this->getVx() >= 0) {
			if (this->getIsConverting()) {
				this->setIsConverting(false);
				this->setState(MarioState::WALKING);
			}
		}
	}
	else if (this->getTargetVx() < 0) {
		if (this->getVx() + this->getAccelerationX() >= this->getTargetVx()) {
			this->plusVx(this->getAccelerationX());
		}
		/*else {
			this->setVx(this->getTargetVx());
		}*/

		// Stop Converting
		if (this->getVx() <= 0) {
			if (this->getIsConverting()) {
				this->setIsConverting(false);
				this->setState(MarioState::WALKING);
			}
		}
	}
	else { // = 0
		if (this->getIsFlip() == false) { // -->
			if (this->getVx() + this->getAccelerationX() > 0) {
				this->plusVx(this->getAccelerationX());
			}
			else {
				this->setVx(0);
				if (this->getIsReduceWalking() && this->getState() == WALKING) {
					this->setState(MarioState::STANDING);
				}
			}
		}
		else { // <--
			if (this->getVx() + this->getAccelerationX() < 0) {
				this->plusVx(this->getAccelerationX());
			}
			else {
				this->setVx(0);
				if (this->getIsReduceWalking() && this->getState() == WALKING) {
					this->setState(MarioState::STANDING);
				}
			}
		}
	}

	if (this->getTargetVy() > 0) {
		if (this->getVy() + this->getAccelerationY() <= this->getTargetVy()) {
			this->plusVy(this->getAccelerationY());
		}
		/*else {
			this->setVy(this->getTargetVy());
		}*/
	}
	else if (this->getTargetVy() == 0) {
		if (this->getState() == JUMPING) {
			if (this->getVy() + this->getAccelerationY() < 0) {
				this->plusVy(this->getAccelerationY());
			}
			else {
				this->setState(MarioState::DROPPING);
			}
		}
		else if (this->getState() == DIE_JUMPING) {
			if (this->getVy() + this->getAccelerationY() < 0) {
				this->plusVy(this->getAccelerationY());
			}
			else {
				this->setState(MarioState::DIE_DROPPING);
			}
		}
	}
}

void Mario::increasePointCoef()
{
	this->pointCoef += 1;
}

void Mario::resetPointCoef()
{
	this->pointCoef = 0;
}

void Mario::setLeftSpace(int _space)
{
	this->leftSpace = _space;
}

void Mario::setTopSpace(int _space)
{
	this->topSpace = _space;
}

void Mario::setRightSpace(int _space)
{
	this->rightSpace = _space;
}

void Mario::setMarioLeftSpace(int _space)
{
	this->marioLeftSpace = _space;
}

void Mario::setMarioTopSpace(int _space)
{
	this->marioTopSpace = _space;
}

void Mario::setMarioRightSpace(int _space)
{
	this->marioRightSpace = _space;
}

void Mario::setSuperMarioLeftSpace(int _space)
{
	this->superMarioLeftSpace = _space;
}

void Mario::setSuperMarioTopSpace(int _space)
{
	this->superMarioTopSpace = _space;
}

void Mario::setSuperMarioRightSpace(int _space)
{
	this->superMarioRightSpace = _space;
}

void Mario::setSuperMarioFlyingLeftSpace(int _space)
{
	this->superMarioFlyingLeftSpace = _space;
}

void Mario::setSuperMarioFlyingTopSpace(int _space)
{
	this->superMarioFlyingTopSpace = _space;
}

void Mario::setSuperMarioFlyingRightSpace(int _space)
{
	this->superMarioFlyingRightSpace = _space;
}

void Mario::setFirstFireBallState(FireBallState _state)
{
	this->firstFireBall->setState(_state);
}

void Mario::setMomentumLevel(int _momentumLevel)
{
	this->momentumLevelToFly = _momentumLevel;
	if (this->momentumLevelToFly < 7) {
		if (this->getIsPreFlyingUpMode()) {
			this->setIsPreFlyingUpMode(false);
			if (this->getIsPreFlyingUpMode()) {
				this->turnOnPreFlyingUpSkin();
			}
			else {
				this->turnOffPreFlyingUpSkin();
			}
		}
	}
}

void Mario::setMomentum(int _momentum)
{
	this->momentumToFly = _momentum;
	this->setMomentumLevel(this->momentumToFly / this->momentumSpace);
	if (this->momentumLevelToFly < 0) {
		this->setMomentumLevel(0);
	}
	else if (this->momentumLevelToFly > 7) {
		this->setMomentumLevel(7);
	}
}

void Mario::plusMomentum(int _momentum)
{
	this->momentumToFly += _momentum;
	this->setMomentumLevel(this->momentumToFly / this->momentumSpace);
	if (this->momentumLevelToFly < 0) {
		this->setMomentumLevel(0);
	}
	else if (this->momentumLevelToFly > 7) {
		this->setMomentumLevel(7);
	}
}

void Mario::onKeyUp()
{
	if (this->getState() == WALKING) {
		//this->setState(MarioState::STANDING);
		this->setupReduceWalking(true);
		this->setIsConverting(false);
	}
	else if (this->getState() == DROPPING) {
		if (this->getVx() < 0) {
			this->setAccelerationX(0.1);
		}
		else if (this->getVx() > 0) {
			this->setAccelerationX(-0.1);
		}
		if (this->getTargetVx() != 0) {
			this->setTargetVx(0);
		}
	}

	if (this->getIsFlyingUpMode() == false) {
		this->setMomentum(0);
	}
}

void Mario::onKeyUp(vector<KeyType> _keyTypes)
{
	bool noLeft = false, noRight = false;
	for (int i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == KeyType::key_S) {
			if (this->getState() == JUMPING) {
				this->setState(MarioState::DROPPING);
			}
		}
		else if (_keyTypes[i] == KeyType::right) {
			noRight = true;
			if (this->getSubState() == PUSHING) {
				this->setSubState(MarioSubState::NONE);
			}
		}
		else if (_keyTypes[i] == KeyType::left) {
			noLeft = true;
			if (this->getSubState() == PUSHING) {
				this->setSubState(MarioSubState::NONE);
			}
		}
		else if (_keyTypes[i] == KeyType::key_A) {
			if (this->getIsFlyingUpMode() == false) {
				this->setMomentum(0);
			}
			this->setIsPressA(false);
		}
	}
	
	if (noLeft && noRight) {
		if (this->getIsFlyingUpMode() == false) {
			this->setMomentum(0);
		}
	}
}

void Mario::onKeyDown(vector<KeyType> _keyTypes)
{
	bool hasKeyRight = false;
	bool hasKeyLeft = false;

	for (int i = 0; i < _keyTypes.size(); ++i) {
		// Right
		if (_keyTypes[i] == KeyType::right) {
			if (this->getSubState() == PUSHING) {
				continue;
			}
			hasKeyRight = true;

			if (!hasKeyLeft) {
				this->setIsFlip(false);
				if (this->getState() == DROPPING || this->getState() == JUMPING) {
					this->setTargetVx(1.2);
				}
				else {
					this->setTargetVx(2.1);
					if (this->getVx() < 0) {
						this->setIsConverting(true);
						this->setState(MarioState::WALKING);
					}
				}
				this->setAccelerationX(0.15);
			}
			else {
				this->setTargetVx(0);
				this->setIsConverting(false);
				if (this->getVx() > this->getTargetVx()) {
					this->setAccelerationX(-0.1);
				}
				else if (this->getVx() < this->getTargetVx()) {
					this->setAccelerationX(0.1);
				}
				else {
					this->setAccelerationX(0);
				}
			}
		}
		
		// Left
		else if (_keyTypes[i] == KeyType::left) {
			if (this->getSubState() == PUSHING) {
				continue;
			}
			hasKeyLeft = true;

			if (!hasKeyRight) {
				this->setIsFlip(true);
				if (this->getState() == DROPPING || this->getState() == JUMPING) {
					this->setTargetVx(-1.2);
				}
				else {
					this->setTargetVx(-2.1);
					if (this->getVx() > 0) {
						this->setIsConverting(true);
						this->setState(MarioState::WALKING);
					}
				}
				this->setAccelerationX(-0.15);
			}
			else {
				this->setTargetVx(0);
				this->setIsConverting(true);
				if (this->getVx() > this->getTargetVx()) {
					this->setAccelerationX(-0.1);
				}
				else if (this->getVx() < this->getTargetVx()) {
					this->setAccelerationX(0.1);
				}
				else {
					this->setAccelerationX(0);
				}
			}
		}
		
		// Turning around
		else if (_keyTypes[i] == KeyType::key_A) {
			if (this->getIsFlyingMode() && this->getIsPressA() == false) {
				this->setIsTurningAround(true);
				this->setIsPressA(true);
				this->turnOnTurningAroundSkin();
			}
		}

		// Jump
		else if (_keyTypes[i] == KeyType::key_S) {
			if (this->getIsPreFlyingUpMode()) {
				if (this->getIsFlyingUpMode() == false) {
					this->setIsFlyingUpMode(true);
				}
				if (this->getIsFlyingUpMode()) {
					this->setState(MarioState::JUMPING);
				}
			}
			else if (this->getState() == DROPPING) {
				return;
			}
			else if (this->getState() == STANDING || this->getState() == WALKING) {
				this->setState(MarioState::JUMPING);
			}
		}

		// Shoot Fire Ball
		else if (_keyTypes[i] == KeyType::key_D) {
			if (this->getIsFireMode() && this->firstFireBall->getIsOutOfGrid()) {
				if (this->getIsFlip()) {
					this->firstFireBall->setX(this->getX());
					this->firstFireBall->setY(this->getY());
					this->firstFireBall->setTopAnchor(this->getY() - 16);
					this->firstFireBall->setState(FireBallState::FIREBALL_FLYING_LEFT);
					this->firstFireBall->setIsGoDown(true);
				}
				else {
					this->firstFireBall->setX(this->getX() + this->getWidth());
					this->firstFireBall->setY(this->getY());
					this->firstFireBall->setTopAnchor(this->getY() - 16);
					this->firstFireBall->setState(FireBallState::FIREBALL_FLYING_RIGHT);
					this->firstFireBall->setIsGoDown(true);
				}
				Grid::getInstance()->add(this->firstFireBall);
				Grid::getInstance()->updateCellOf(this->firstFireBall);
				this->firstFireBall->setIsOutOfGrid(false);
			}
		}

		// Fire Mode
		else if (_keyTypes[i] == KeyType::F3) {
			if (this->getIsFireMode() == false) {
				this->turnOnFireSkin(this->getState());
			}
		}
		else if (_keyTypes[i] == KeyType::F4) {
			if (this->getIsFireMode() == true) {
				this->turnOffFireSkin(this->getState());
			}
		}

	}
	

	if (this->getTargetVx() == 0 && this->getState() == WALKING) {
		this->setState(MarioState::STANDING);
	}
	if (this->getTargetVx() != 0 && this->getState() == STANDING) {
		this->setState(MarioState::WALKING);
	}
}

void Mario::handleGroundCollision(Ground* _ground, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_ground, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge) {
				this->setState(MarioState::DROPPING);
				this->setY(_ground->getY() + _ground->getHeight());
				this->setVy(0);
			}
			else if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_ground->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
			}
			else if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _ground->getY()) {
				this->setX(_ground->getX() + _ground->getWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _ground->getY()) {
				this->setX(_ground->getX() - this->getBoundsWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_ground->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _ground->getX() + _ground->getWidth())
					|| (_ground->getX() <= this->getX() && this->getX() <= _ground->getX() + _ground->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _ground->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleBlockCollision(Block* _block, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_block, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_block->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_block->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _block->getX() + _block->getWidth())
					|| (_block->getX() <= this->getX() && this->getX() <= _block->getX() + _block->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _block->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleGoldenBrickCollision(GoldenBrick* _goldenBrick, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_goldenBrick, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge) {
				this->setState(MarioState::DROPPING);
				this->setY(_goldenBrick->getY() + _goldenBrick->getHeight());
				this->setVy(0);
			}
			else if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_goldenBrick->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
			}
			else if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _goldenBrick->getY()) {
				this->setX(_goldenBrick->getX() + _goldenBrick->getWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _goldenBrick->getY()) {
				this->setX(_goldenBrick->getX() - this->getBoundsWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_goldenBrick->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _goldenBrick->getX() + _goldenBrick->getWidth())
					|| (_goldenBrick->getX() <= this->getX() && this->getX() <= _goldenBrick->getX() + _goldenBrick->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _goldenBrick->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleGiftBrickCollision(GiftBrick* _giftBrick, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_giftBrick, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge) {
				if (_giftBrick->getState() == FULLGIFTBRICK) {
					if (_giftBrick->getGiftType() == NotPoint) {
						if (this->getIsSuperMode() == false) {
							_giftBrick->setGiftType(GiftType::SuperMushroomGift);
						}
						else {
							_giftBrick->plusY(this->getVy() * _dt + (_giftBrick->getHeight() / 2));
							_giftBrick->setGiftType(GiftType::SuperLeafGift);
						}
					}
					_giftBrick->setState(GiftBrickState::POPUPGIFTBRICK);
					if (_giftBrick->getGiftType() == Point100Gift) {
						ScoreBoard::getInstance()->plusCoin(1);
						ScoreBoard::getInstance()->plusPoint(100);
					}
				}
				this->setState(MarioState::DROPPING);
				this->setY(_giftBrick->getY() + _giftBrick->getHeight());
				this->setVy(0);
			}
			else if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_giftBrick->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
			}
			else if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _giftBrick->getY()/* && (this->getState() == JUMPING || this->getState() == DROPPING) */) {
				this->setX(_giftBrick->getX() + _giftBrick->getWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _giftBrick->getY()/* && (this->getState() == JUMPING || this->getState() == DROPPING)*/) {
				this->setX(_giftBrick->getX() - this->getBoundsWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_giftBrick->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _giftBrick->getX() + _giftBrick->getWidth())
					|| (_giftBrick->getX() <= this->getX() && this->getX() <= _giftBrick->getX() + _giftBrick->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _giftBrick->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleGreenPipeCollision(GreenPipe* _greenPipe, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_greenPipe, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge) {
				this->setState(MarioState::DROPPING);
				this->setY(_greenPipe->getY() + _greenPipe->getHeight());
				this->setVy(0);
			}
			else if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_greenPipe->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
			}
			else if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _greenPipe->getY()) {
				this->setX(_greenPipe->getX() + _greenPipe->getWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _greenPipe->getY()) {
				this->setX(_greenPipe->getX() - this->getBoundsWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_greenPipe->getX() <= this->getX() + this->getBoundsWidth() && this->getX() + this->getBoundsWidth() <= _greenPipe->getX() + _greenPipe->getWidth())
					|| (_greenPipe->getX() <= this->getX() && this->getX() <= _greenPipe->getX() + _greenPipe->getWidth())) { // this is check which ground that mario is standing on
					if (this->getY() + this->getBoundsHeight() == _greenPipe->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleGoombaCollision(Goomba* _goomba, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getIsFlashMode()) {
		return;
	}

	if (_goomba->getState() == TRAMPLED_GOOMBA
		|| _goomba->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| _goomba->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| _goomba->getState() == DEAD_GOOMBA) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_goomba, _dt);
	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == bottomEdge && this->getState() == DROPPING) {
			this->plusY(get<1>(collisionResult) * this->getVy() + _goomba->getHeight() / 4);
			this->setState(MarioState::JUMPING);
			_goomba->setState(GoombaState::TRAMPLED_GOOMBA);

			// Calculate points
			this->increasePointCoef();
			_goomba->setPointCoef(this->getPointCoef());
			ScoreBoard::getInstance()->plusPoint(_goomba->getDefaultPoint() * _goomba->getPointCoef());
		}
		else if (edge == leftEdge) {
			_goomba->plusX(2 * get<1>(collisionResult) * _goomba->getVx());
			if (this->getIsSuperMode() == false) {
				_goomba->setState(GoombaState::GOOMBA_STANDING);
			}
			this->plusX(get<1>(collisionResult) * this->getVx());
			this->setState(MarioState::DIE);
		}
		else if (edge == rightEdge) {
			_goomba->plusX(2 * get<1>(collisionResult) * _goomba->getVx());
			if (this->getIsSuperMode() == false) {
				_goomba->setState(GoombaState::GOOMBA_STANDING);
			}
			this->plusX(get<1>(collisionResult) * this->getVx());
			this->setState(MarioState::DIE);
		}
		else if (edge == topEdge) {
			_goomba->plusX(2 * get<1>(collisionResult) * _goomba->getVx());
			_goomba->plusY(2 * get<1>(collisionResult) * _goomba->getVy());
			if (this->getIsSuperMode() == false) {
				_goomba->setState(GoombaState::GOOMBA_STANDING);
			}
			this->plusY(get<1>(collisionResult) * this->getVy());
			this->setState(MarioState::DIE);
		}
	}
	else if (this->isCollidingByBounds(_goomba->getBounds())
		&& (this->getState() == WALKING || this->getState() == STANDING)
		&& _goomba->getState() != TRAMPLED_GOOMBA) {
		_goomba->plusX(2 * get<1>(collisionResult) * _goomba->getVx());
		if (this->getIsSuperMode() == false) {
			_goomba->setState(GoombaState::GOOMBA_STANDING);
		}
		this->plusX(get<1>(collisionResult) * this->getVx());
		this->setState(MarioState::DIE);
	}
}

void Mario::handleKoopaCollision(Koopa* _koopa, float _dt)
{
	if (_koopa->getState() == KOOPA_THROWN_LEFT_AWAY || _koopa->getState() == KOOPA_THROWN_RIGHT_AWAY) return;

	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getIsFlashMode()) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_koopa, _dt);

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == leftEdge) {
			if (_koopa->getState() == KOOPA_SHRINKAGE || _koopa->getState() == KOOPA_SHRINKAGE_SHAKING) {
				_koopa->plusX(this->getVx() * _dt - (this->getBoundsWidth() / 2));
				_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				//this->plusX(get<1>(collisionResult) * this->getVx());
			}
			else {
				if (this->getIsSuperMode() == false) {
					_koopa->plusX(get<1>(collisionResult) * _koopa->getVx());
					_koopa->setState(KoopaState::KOOPA_STANDING);
				}

				this->plusX(get<1>(collisionResult)* this->getVx());
				this->setState(MarioState::DIE);
			}
		}
		else if (edge == rightEdge) {
			if (_koopa->getState() == KOOPA_SHRINKAGE || _koopa->getState() == KOOPA_SHRINKAGE_SHAKING) {
				_koopa->plusX((this->getVx() * _dt) + (this->getBoundsWidth() / 2));
				_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
				//this->plusX(get<1>(collisionResult) * this->getVx());
			}
			else {
				if (this->getIsSuperMode() == false) {
					_koopa->plusX(get<1>(collisionResult) * _koopa->getVx());
					_koopa->setState(KoopaState::KOOPA_STANDING);
				}
				this->plusX(get<1>(collisionResult)* this->getVx());
				this->setState(MarioState::DIE);
			}
		}
		else if (edge == topEdge) {
			if (this->getIsSuperMode() == false) {
				_koopa->plusX(get<1>(collisionResult) * _koopa->getVx());
				_koopa->plusY(get<1>(collisionResult) * _koopa->getVy());
				_koopa->setState(KoopaState::KOOPA_STANDING);
			}

			this->plusX(get<1>(collisionResult)* this->getVx());
			this->plusY(get<1>(collisionResult) * this->getVy());
			this->setState(MarioState::DIE);
		}
		else if (edge == bottomEdge && this->getState() == DROPPING) {
			this->plusY(get<1>(collisionResult) * this->getVy() + _koopa->getHeight() / 4);
			this->setState(MarioState::JUMPING);

			// Calculate points
			this->increasePointCoef();
			_koopa->setPointCoef(this->getPointCoef());
			ScoreBoard::getInstance()->plusPoint(_koopa->getDefaultPoint() * _koopa->getPointCoef());

			if (_koopa->getState() == KOOPA_SHRINKAGE) {
				float centerMario = this->getX() + this->getBoundsWidth() / 2;
				float centerKoopa = _koopa->getX() + _koopa->getWidth() / 2;

				if (centerMario >= centerKoopa) {
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				}
				else {
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
				}
			}
			else {
				_koopa->setState(KoopaState::KOOPA_SHRINKAGE);
			}

			_koopa->setupPointAnimPosition();
		}
	}
	else if (this->isCollidingByBounds(_koopa->getBounds())
		&& (this->getState() == WALKING || this->getState() == STANDING)
			&& _koopa->getState() != KOOPA_SHRINKAGE && _koopa->getState() != KOOPA_SHRINKAGE_SHAKING) {
		_koopa->plusX(2 * get<1>(collisionResult) * _koopa->getVx());
		if (this->getIsSuperMode() == false) {
			_koopa->setState(KoopaState::KOOPA_STANDING);
		}
		this->plusX(get<1>(collisionResult) * this->getVx());
		this->setState(MarioState::DIE);
	}
}

void Mario::handleSuperMushroomCollision(SuperMushroom* _superMushroom, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getIsFlashMode()) {
		return;
	}

	if (_superMushroom->getState() == SUPER_MUSHROOM_BEING_EARNED
	||_superMushroom->getState() == SUPER_MUSHROOM_DISAPPEARED) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_superMushroom, _dt);

	if (get<0>(collisionResult) == true) {
		int xPoint = _superMushroom->getX();
		int yPoint = _superMushroom->getY();

		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_superMushroom->getDefaultPoints(), xPoint, yPoint)));
		ScoreBoard::getInstance()->plusPoint(1000);

		//_superMushroom->plusX(this->getVx() * get<1>(collisionResult));
		//_superMushroom->plusY(this->getVy() * get<1>(collisionResult));
		_superMushroom->setState(SuperMushroomState::SUPER_MUSHROOM_BEING_EARNED);
		this->plusX(this->getVx() * get<1>(collisionResult));
		this->plusY(this->getVy() * get<1>(collisionResult));
		if (this->getIsSuperMode() == false) {
			this->setState(MarioState::SCALING_UP);
		}
	}
	else if (this->isCollidingByBounds(_superMushroom->getBounds())) {
		int xPoint = _superMushroom->getX();
		int yPoint = _superMushroom->getY();

		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_superMushroom->getDefaultPoints(), xPoint, yPoint)));
		ScoreBoard::getInstance()->plusPoint(1000);

		_superMushroom->setState(SuperMushroomState::SUPER_MUSHROOM_BEING_EARNED);
		if (this->getIsSuperMode() == false) {
			this->setState(MarioState::SCALING_UP);
		}
	}
}

void Mario::handleSuperLeafCollision(SuperLeaf* _superLeaf, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getIsFlashMode()
		|| _superLeaf->getState() == SUPER_LEAF_BEING_EARNED) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_superLeaf, _dt);

	if (get<0>(collisionResult) == true) {
		//int xPoint = _superLeaf->getX();
		//int yPoint = _superLeaf->getY();

		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_superLeaf->getDefaultPoints(), _superLeaf->getX(), _superLeaf->getY())));
		ScoreBoard::getInstance()->plusPoint(1000);

		_superLeaf->plusX(_superLeaf->getVx() * get<1>(collisionResult));
		_superLeaf->plusY(_superLeaf->getVy() * get<1>(collisionResult));
		_superLeaf->setState(SuperLeafState::SUPER_LEAF_BEING_EARNED);
		this->plusX(this->getVx() * get<1>(collisionResult));
		this->plusY(this->getVy() * get<1>(collisionResult));

		if (this->getIsFlyingMode() == false) {
			this->setState(MarioState::TRANSFERING_TO_FLY);
		}

	}
	else if (this->isCollidingByBounds(_superLeaf->getBounds())) {
		//int xPoint = _superLeaf->getX();
		//int yPoint = _superLeaf->getY();

		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_superLeaf->getDefaultPoints(), _superLeaf->getX(), _superLeaf->getY())));
		ScoreBoard::getInstance()->plusPoint(1000);

		_superLeaf->setState(SuperLeafState::SUPER_LEAF_BEING_EARNED);

		if (this->getIsFlyingMode() == false) {
			this->setState(MarioState::TRANSFERING_TO_FLY);
		}
	}
}

void Mario::handleFireFlowerCollision(FireFlower* _fireFlower, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getIsFlashMode()) {
		return;
	}

	if (_fireFlower->getState() == FIRE_FLOWER_HIDING || _fireFlower->getState() == FIRE_FLOWER_DEAD) return;
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_fireFlower, _dt);

	if (get<0>(collisionResult) == true) {
		this->plusX(this->getVx() * get<1>(collisionResult));
		this->plusY(this->getVy() * get<1>(collisionResult));
		this->setState(MarioState::DIE);
	}
	else if (this->isCollidingByBounds(_fireFlower->getBounds())) {
		this->setState(MarioState::DIE);
	}
}

void Mario::handleFireFlowerBallCollision(FireFlowerBall* _fireFlowerBall, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getIsFlashMode()) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_fireFlowerBall, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_fireFlowerBall->getBounds())) {
		_fireFlowerBall->plusX(get<1>(collisionResult) * _fireFlowerBall->getVx());
		_fireFlowerBall->plusY(get<1>(collisionResult) * _fireFlowerBall->getVy());
		this->setState(MarioState::DIE);
	}
}

void Mario::handleFlowerCollision(Flower* _flower, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getIsFlashMode()) {
		return;
	}

	if (_flower->getState() == FLOWER_HIDING || _flower->getState() == FLOWER_DEAD) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_flower, _dt);

	if (get<0>(collisionResult) == true) {
		this->plusX(this->getVx() * get<1>(collisionResult));
		this->plusY(this->getVy() * get<1>(collisionResult));
		this->setState(MarioState::DIE);
	}
	else if (this->isCollidingByBounds(_flower->getBounds())) {
		this->setState(MarioState::DIE);

	}
}

void Mario::handleCoinCollision(Coin* _coin, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getIsFlashMode()) {
		return;
	}

	if (_coin->getState() == COIN_BEING_EARNED) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_coin, _dt);

	if (get<0>(collisionResult) == true) {
		_coin->setState(CoinState::COIN_BEING_EARNED);
		this->plusX(get<1>(collisionResult) * this->getVx());
		this->plusY(get<1>(collisionResult) * this->getVy());
	}
	else {
		if (this->isCollidingByBounds(_coin->getBounds())) {
			_coin->setState(CoinState::COIN_BEING_EARNED);
		}
	}
}
