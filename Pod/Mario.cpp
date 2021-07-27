#include "Mario.h"

Mario::Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY)
{
	MainCharacter::MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY);

	//this->texture = LoadTextureFromImage(_imagePath, _transcolor);
}

Mario::Mario(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : MainCharacter(_position, _vx, _vy, _limitX, _limitY)
{
	MainCharacter::MainCharacter(_position, _vx, _vy, _limitX, _limitY);

	//this->texture = LoadTextureFromImage(_imagePath, _transcolor);
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
	r.top = int(this->getY());
	r.bottom = r.top + this->getBoundsHeight();
	r.left = int(this->getX());
	r.right = r.left + this->getBoundsWidth();

	return r;
}

RECT Mario::getFrame()
{
	RECT r = RECT();
	r.top = int(this->getY()) - this->getTopSpace();
	r.bottom = r.top + this->getHeight();
	r.left = int(this->getX()) - this->getLeftSpace();
	r.right = r.left + this->getWidth();

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

int Mario::getBoundsWidth()
{
	return this->currentAnimation->getCurrentBoundsWidth();
}

int Mario::getBoundsHeight()
{
	return this->currentAnimation->getCurrentBoundsHeight();
}

int Mario::getWidth()
{
	return this->currentAnimation->getCurrentFrameWidth();
}

int Mario::getHeight()
{
	return this->currentAnimation->getCurrentFrameHeight();
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

int Mario::getTailMarginTop()
{
	return this->tailMarginTop;
}

int Mario::getTailHeight()
{
	return this->tailHeight;
}

int Mario::getTailMarginBottom()
{
	return this->tailMarginBottom;
}

int Mario::getNumberBombsAttached()
{
	return this->numberBombsAttached;
}

int Mario::getComponentIdStandingOn()
{
	return this->componentIdStandingOn;
}

int Mario::getEndDroppingDownPipe()
{
	return this->endDroppingDownPipe;
}

int Mario::getEndPoppingUpPipe()
{
	return this->endPoppingUpPipe;
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

bool Mario::getIsPressKeyUp()
{
	return this->isPressKeyUp;
}

bool Mario::getIsPressKeyS()
{
	return this->isPressKeyS;
}

void Mario::load()
{
	fstream fs;
	fs.open(FilePath::getInstance()->mario, ios::in);

	vector<string> v;
	string line;

	while (!fs.eof())
	{
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty
		v = Tool::splitToVectorStringFrom(line, ',');
	}

	fs.close();

	//this->setX(stof(v[0]));
	//this->setY(stof(v[1]));
	//this->setLimitX(stof(v[2]));
	//this->setLimitY(stof(v[3]));
	this->setLeftSpace(stoi(v[0]));
	this->setTopSpace(stoi(v[1]));
	this->setRightSpace(stoi(v[2]));
	this->setMarioLeftSpace(stoi(v[3]));
	this->setMarioTopSpace(stoi(v[4]));
	this->setMarioRightSpace(stoi(v[5]));
	this->setSuperMarioLeftSpace(stoi(v[6]));
	this->setSuperMarioTopSpace(stoi(v[7]));
	this->setSuperMarioRightSpace(stoi(v[8]));
	this->setSuperMarioFlyingLeftSpace(stoi(v[9]));
	this->setSuperMarioFlyingTopSpace(stoi(v[10]));
	this->setSuperMarioFlyingRightSpace(stoi(v[11]));
	//this->setState(Tool::getMarioStateFromString(v[4]));

	this->firstFireBall = new FireBall(0, 0, stof(v[12]), stof(v[13]), 0, 0, stoi(v[14]));
	this->setTailMarginTop(stoi(v[15]));
	this->setTailMarginBottom(stoi(v[16]));
	this->setTailHeight(stoi(v[17]));

	this->setIsFireMode(stoi(v[18]) == 1);
	this->setIsSuperMode(stoi(v[19]) == 1);
	this->setIsFlyingMode(stoi(v[20]) == 1);

	if (this->getIsFlyingMode()) {
		this->setLeftSpace(this->getSuperMarioFlyingLeftSpace());
		this->setTopSpace(this->getSuperMarioFlyingTopSpace());
		this->setRightSpace(this->getSuperMarioFlyingRightSpace());
	}
	else if (this->getIsSuperMode()) {
		this->setLeftSpace(this->getSuperMarioLeftSpace());
		this->setTopSpace(this->getSuperMarioTopSpace());
		this->setRightSpace(this->getSuperMarioRightSpace());
	}
	else {
		this->setLeftSpace(this->getMarioLeftSpace());
		this->setTopSpace(this->getMarioTopSpace());
		this->setRightSpace(this->getMarioRightSpace());
	}
}

void Mario::loadInfo(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setLimitX(v[2]);
	this->setLimitY(v[3]);
}

void Mario::save()
{
	vector<string> data = vector<string>();
	string line = "";

	data.push_back("# (leftSpace, topSpace, rightSpace,");
	data.push_back("\n");
	data.push_back("# marioLeftSpace, marioTopSpace, marioRightSpace,");
	data.push_back("\n");
	data.push_back("# superMarioLeftSpace, superMarioTopSpace, superMarioRightSpace,");
	data.push_back("\n");
	data.push_back("# superMarioFlyingLeftSpace, superMarioFlyingTopSpace, superMarioFlyingRightSpace,");
	data.push_back("\n");
	data.push_back("# firstFireBallVx, firstFireBallVy, firstFireBallId,");
	data.push_back("\n");
	data.push_back("# tailMarginTop, tailMarginBottom, tailHeight,");
	data.push_back("\n");
	data.push_back("# isFireMode, isSuperMode, isFlyingMode)");
	data.push_back("\n");

	/*line += to_string(this->getLeftSpace());
	line += ",";
	line += to_string(this->getTopSpace());
	line += ",";
	line += to_string(this->getRightSpace());
	line += ",";
	line += to_string(this->getMarioLeftSpace());
	line += ",";
	line += to_string(this->getMarioTopSpace());
	line += ",";
	line += to_string(this->getMarioRightSpace());
	line += ",";
	line += to_string(this->getSuperMarioLeftSpace());
	line += ",";
	line += to_string(this->getSuperMarioTopSpace());
	line += ",";
	line += to_string(this->getSuperMarioRightSpace());
	line += ",";
	line += to_string(this->getSuperMarioFlyingLeftSpace());
	line += ",";
	line += to_string(this->getSuperMarioFlyingTopSpace());
	line += ",";
	line += to_string(this->getSuperMarioFlyingRightSpace());
	line += ",";
	line += to_string(this->firstFireBall->getVx());
	line += ",";
	line += to_string(this->firstFireBall->getVy());
	line += ",";
	line += to_string(this->firstFireBall->getId());
	line += ",";
	line += to_string(this->getTailMarginTop());
	line += ",";
	line += to_string(this->getTailMarginBottom());
	line += ",";
	line += to_string(this->getTailHeight());
	line += ",";
	*/
	line += "4,3,2,4,3,2,3,5,1,10,6,1,5,1,1001,20,6,4";
	line += ",";
	line += to_string(this->getIsFireMode());
	line += ",";
	line += to_string(this->getIsSuperMode());
	line += ",";
	line += to_string(this->getIsFlyingMode());

	data.push_back(line);

	fstream fs;
	fs.open(FilePath::getInstance()->mario, ios::out);

	for (size_t i = 0; i < data.size(); ++i) {
		if (data[i] == "\n") {
			fs << endl;
		}
		else {
			fs << data[i];
		}
	}

	fs.close();
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
		if (this->getIsFlyingMode() == false) {
			this->setIsFlashMode(true);
			this->countDownFlash = 120;
		}
	}

	switch (_state)
	{
	case STANDING:
	{
		this->setIsFlyingUpMode(false);
		this->setIsReduceWalking(false);
		this->resetPointCoef();
		if (this->getState() != STANDING || this->currentAnimation == NULL) {
			if (this->getIsTurningAround()) {
				this->setIsTurningAround(false);
			}
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

		if (this->getIsTurningAround()) {
			this->setIsTurningAround(false);
		}
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

			if (this->getIsTurningAround()) {
				this->setIsTurningAround(false);
			}
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
		this->setVy(this->getIsSuperMode() ? float(-4.4) : float(-4.0));
		this->setAccelerationY(float(0.11));
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
		this->setAccelerationY(float(0.11));
		this->setVx(0);
		this->setVy(float(-4.4));
		break;
	}

	case DIE_DROPPING:
	{
		this->setTargetVx(0);
		this->setTargetVy(6);
		this->setAccelerationX(0);
		this->setAccelerationY(float(0.34));
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
		this->countDownFlash = 120;

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

	case DROPPING_DOWN_PIPE:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			if (this->getIsFireMode()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireDroppingDownPipe());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingDroppingDownPipe());
			}
		}
		else if (this->getIsSuperMode()) {
			if (this->getIsFireMode()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireDroppingDownPipe());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioDroppingDownPipe());
			}
		}
		else {
			if (this->getIsFireMode()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireDroppingDownPipe());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDroppingDownPipe());
			}
		}
		
		this->endDroppingDownPipe = int(this->getY()) + this->getHeight();
		break;
	}

	case POPPING_UP_PIPE:
	{
		delete currentAnimation;
		if (this->getIsFlyingMode()) {
			if (this->getIsFireMode()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireDroppingDownPipe());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingDroppingDownPipe());
			}
		}
		else if (this->getIsSuperMode()) {
			if (this->getIsFireMode()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFireDroppingDownPipe());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioDroppingDownPipe());
			}
		}
		else {
			if (this->getIsFireMode()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioFireDroppingDownPipe());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDroppingDownPipe());
			}
		}
		this->endPoppingUpPipe = int(this->getY()) - this->getBoundsHeight();
		break;
	}

	default:
		break;
	}


	// Change position when frame anim size change
	this->newFrameWidth = this->currentAnimation->getCurrentBoundsWidth();
	this->newFrameHeight = this->currentAnimation->getCurrentBoundsHeight();

	if (oldFrameWidth != newFrameWidth) {
		this->plusX(float(oldFrameWidth - newFrameWidth));
	}
	if (oldFrameHeight != newFrameHeight) {
		this->plusY(float(oldFrameHeight - newFrameHeight));
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

void Mario::setAnimation(Animation* _animation)
{
	this->currentAnimation = _animation;
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
		this->setAccelerationX(float(0.1));
	}
	else if (this->getVx() > 0) {
		this->setAccelerationX(float(-0.1));
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

void Mario::setIsPressKeyUp(bool _isPressKeyUp)
{
	this->isPressKeyUp = _isPressKeyUp;
}

void Mario::setIsPressKeyS(bool _isPressKeyS)
{
	this->isPressKeyS = _isPressKeyS;
}

void Mario::turnOnTurningAroundSkin()
{
	//this->setPressureState(MarioState(this->getState()));
	this->setPressureAnimation(*currentAnimation);
	if (this->getIsFlip() == false) {
		this->plusX(-1);
	}
	delete currentAnimation;
	if (this->getIsFireMode()) {
		this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingFireTurningAround());
	}
	else {
		this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioFlyingTurningAround());
	}
}

void Mario::turnOffTurningAroundSkin()
{
	if (this->getIsTurningAround()) {
		this->currentAnimation = this->getPressureAnimation();
	}
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

	if (this->getState() == DROPPING_DOWN_PIPE) {
		this->plusY(1);
		return;
	}
	else if (this->getState() == POPPING_UP_PIPE) {
		this->plusY(-1);
		return;
	}
	else if (this->getState() == JUMPING_UP_TO_CLOUND) {
		this->plusY(-6);
		return;
	}

	if (this->getIsTurningAround()) {
		if (this->currentAnimation->getCurrentIndexFrame() >= this->currentAnimation->getTotalFrames() - 1
			&& this->currentAnimation->getAnimCount() >= this->currentAnimation->getAnimDelay()) {
			this->turnOffTurningAroundSkin();
			this->setIsTurningAround(false);
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
	if (this->firstBombAnim != NULL) {
		this->firstBombAnim->Update(_dt);
	}
	if (this->secondBombAnim != NULL) {
		this->secondBombAnim->Update(_dt);
	}
	if (this->thirdBombAnim != NULL) {
		this->thirdBombAnim->Update(_dt);
	}

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
	this->updateVelocity(_dt);
	if (this->getX() + round(this->getVx() * _dt) >= 0
		&& this->getX() + this->getBoundsWidth() + round(this->getVx() * _dt) <= this->getLimitX()
		&& this->getSubState() != PUSHING) {
		this->plusX(this->getVx() * _dt);
	}
	if (this->getY() + round(this->getVy() * _dt) > 0) {
		this->plusY(this->getVy() * _dt);
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
		this->currentAnimation->DrawMarioWithoutCamera(Drawing::getInstance()->getMarioTexture(), this->getPosition(), D3DXVECTOR2(translateX, translateY), this->getLeftSpace(), this->getTopSpace(), this->getRightSpace(), this->getIsFlip(), ((this->countDownFlash % 4 == 0 || this->countDownFlash % 3 == 0) ? D3DCOLOR_ARGB(128, 255, 255, 255) : D3DCOLOR_XRGB(255, 255, 255)));
		//this->currentAnimation->DrawWithoutCamera(this->texture, this->getPosition(), D3DXVECTOR2(translateX - transX, translateY - this->getTopSpace()), this->getIsFlip(), (this->countDownFlash % 4 == 0 ? D3DCOLOR_ARGB(128, 255, 255, 255) : D3DCOLOR_XRGB(255, 255, 255)));
	}
	else if (this->getState() == SCALING_UP) {
		this->currentAnimation->DrawWithoutCamera(Drawing::getInstance()->getMarioTexture(), this->getPosition(), D3DXVECTOR2(translateX, translateY), this->getIsFlip());
	}
	else {
		this->currentAnimation->DrawMarioWithoutCamera(Drawing::getInstance()->getMarioTexture(), this->getPosition(), D3DXVECTOR2(translateX, translateY), this->getLeftSpace(), this->getTopSpace(), this->getRightSpace(), this->getIsFlip());
		//this->currentAnimation->DrawWithoutCamera(this->texture, this->getPosition(), D3DXVECTOR2(translateX - transX, translateY - this->getTopSpace()), this->getIsFlip(), D3DCOLOR_XRGB(255, 255, 255));
	}

	if (this->getNumberBombsAttached() > 0) {
		if (this->getNumberBombsAttached() >= 3) {
			if (this->thirdBombAnim == NULL) {
				this->thirdBombAnim = new Animation(AnimationBundle::getInstance()->getBombAttachedMario());
			}
			Drawing::getInstance()->draw(Drawing::getInstance()->getSunnyMapTexture(), this->thirdBombAnim->getCurrentFrame(), D3DXVECTOR3(this->getX() - 5, this->getY() + (this->getBoundsHeight() - this->thirdBombAnim->getCurrentFrameHeight()), 0));
		}
		if (this->getNumberBombsAttached() >= 2) {
			if (this->secondBombAnim == NULL) {
				this->secondBombAnim = new Animation(AnimationBundle::getInstance()->getBombAttachedMario());
			}
			Drawing::getInstance()->draw(Drawing::getInstance()->getSunnyMapTexture(), this->secondBombAnim->getCurrentFrame(), D3DXVECTOR3(this->getX() - 5, this->getY() + (this->getBoundsHeight() - this->secondBombAnim->getCurrentFrameHeight()), 0));
		}
		if (this->getNumberBombsAttached() >= 1) {
			if (this->firstBombAnim == NULL) {
				this->firstBombAnim = new Animation(AnimationBundle::getInstance()->getBombAttachedMario());
			}
			Drawing::getInstance()->draw(Drawing::getInstance()->getSunnyMapTexture(), this->firstBombAnim->getCurrentFrame(), D3DXVECTOR3(this->getX() - 5, this->getY() + (this->getBoundsHeight() - this->firstBombAnim->getCurrentFrameHeight()), 0));
		}
	}

	// Draw debug box
	if (debugMode == Setting::getInstance()->getDebugMode()) {
		Drawing::getInstance()->drawDebugBoxWithoutCamera(this->getBounds(), NULL, this->getPosition(), D3DXVECTOR2(translateX, translateY), false, D3DCOLOR_ARGB(128, 255, 255, 255));
	}
}

void Mario::updateVelocity(float _dt)
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
			if (this->getNumberBombsAttached() > 0) {
				if (this->getVy() + this->getAccelerationY() >= -8) {
					this->plusY(10 * _dt);
					this->setState(MarioState::DROPPING);
				}
				else {
					this->plusVy(this->getAccelerationY());
				}
			}
			else {
				if (this->getVy() + this->getAccelerationY() < 0) {
					this->plusVy(this->getAccelerationY());
				}
				else {
					this->setState(MarioState::DROPPING);
				}
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

void Mario::setTailMarginTop(int _tailMarginTop)
{
	this->tailMarginTop = _tailMarginTop;
}

void Mario::setTailHeight(int _tailHeight)
{
	this->tailHeight = _tailHeight;
}

void Mario::setTailMarginBottom(int _tailMarginBottom)
{
	this->tailMarginBottom = _tailMarginBottom;
}

void Mario::increaseBombAttached()
{
	if (this->numberBombsAttached < 3) {
		this->numberBombsAttached += 1;
	}
}

void Mario::setComponentIdStandingOn(int _componentIdStandingOn)
{
	this->componentIdStandingOn = _componentIdStandingOn;
}

void Mario::onKeyUp()
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN) {
		return;
	}

	if (this->getState() == WALKING) {
		//this->setState(MarioState::STANDING);
		this->setupReduceWalking(true);
		this->setIsConverting(false);
	}
	else if (this->getState() == DROPPING) {
		if (this->getVx() < 0) {
			this->setAccelerationX(float(0.1));
		}
		else if (this->getVx() > 0) {
			this->setAccelerationX(float(-0.1));
		}
		if (this->getTargetVx() != 0) {
			this->setTargetVx(0);
		}
	}

	if (this->getIsFlyingUpMode() == false) {
		this->setMomentum(0);
	}
	this->setIsPressKeyS(false);
}

void Mario::onKeyUp(vector<KeyType> _keyTypes)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN) {
		return;
	}

	bool noLeft = false, noRight = false;
	for (size_t i = 0; i < _keyTypes.size(); ++i) {
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
		else if (_keyTypes[i] == KeyType::up) {
			this->setIsPressKeyUp(false);
		}
		else if (_keyTypes[i] == KeyType::key_S) {
			this->setIsPressKeyS(false);
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
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN) {
		return;
	}

	bool hasKeyRight = false;
	bool hasKeyLeft = false;

	for (size_t i = 0; i < _keyTypes.size(); ++i) {
		// Right
		if (_keyTypes[i] == KeyType::right) {
			if (this->getSubState() == PUSHING) {
				continue;
			}
			hasKeyRight = true;

			if (!hasKeyLeft) {
				this->setIsFlip(false);
				if (this->getState() == DROPPING || this->getState() == JUMPING) {
					this->setTargetVx(float(1.2));
				}
				else {
					this->setTargetVx(float(2.1));
					if (this->getVx() < 0) {
						this->setIsConverting(true);
						this->setState(MarioState::WALKING);
					}
				}
				this->setAccelerationX(float(0.15));
			}
			else {
				this->setTargetVx(0);
				this->setIsConverting(false);
				if (this->getVx() > this->getTargetVx()) {
					this->setAccelerationX(float(-0.1));
				}
				else if (this->getVx() < this->getTargetVx()) {
					this->setAccelerationX(float(0.1));
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
					this->setTargetVx(float(-1.2));
				}
				else {
					this->setTargetVx(float(-2.1));
					if (this->getVx() > 0) {
						this->setIsConverting(true);
						this->setState(MarioState::WALKING);
					}
				}
				this->setAccelerationX(float(-0.15));
			}
			else {
				this->setTargetVx(0);
				this->setIsConverting(true);
				if (this->getVx() > this->getTargetVx()) {
					this->setAccelerationX(float(-0.1));
				}
				else if (this->getVx() < this->getTargetVx()) {
					this->setAccelerationX(float(0.1));
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
			this->setIsPressKeyS(true);
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

		// Small
		else if (_keyTypes[i] == KeyType::number_1) {
			if (this->getIsSuperMode() || this->getIsFlyingMode()) {
				if (this->getState() != MarioState::TRANSFERING_TO_FLY && this->getState() != MarioState::SCALING_UP && this->getState() != MarioState::SCALING_DOWN) {
					this->setState(MarioState::DIE);
				}
			}
		}

		// Big
		else if (_keyTypes[i] == KeyType::number_2) {
			if (this->getIsSuperMode() == false && this->getIsFlyingMode() == false) {
				this->setState(MarioState::SCALING_UP);
			}
		}

		// Tail
		else if (_keyTypes[i] == KeyType::number_3) {
			if (this->getIsSuperMode() == true && this->getIsFlyingMode() == false) {
				this->setState(MarioState::TRANSFERING_TO_FLY);
			}
		}

		// Fire Mode
		else if (_keyTypes[i] == KeyType::number_4) {
			if (this->getIsFireMode() == false) {
				this->turnOnFireSkin(this->getState());
			}
		}
		else if (_keyTypes[i] == KeyType::number_5) {
			if (this->getIsFireMode() == true) {
				this->turnOffFireSkin(this->getState());
			}
		}


		// Keydown
		else if (_keyTypes[i] == KeyType::up) {
			this->setIsPressKeyUp(true);
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
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge
				&& this->getX() != _ground->getX() + _ground->getWidth() && this->getX() + this->getBoundsWidth() != _ground->getX()) {
				this->setState(MarioState::DROPPING);
				this->setY(_ground->getY() + _ground->getHeight());
				this->setVy(0);
			}
			else if (edge == bottomEdge
				&& this->getX() != _ground->getX() + _ground->getWidth() && this->getX() + this->getBoundsWidth() != _ground->getX()) {
				this->setState(MarioState::STANDING);
				this->setY(_ground->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				this->setComponentIdStandingOn(_ground->getId());
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
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge
				&& this->getX() != _block->getX() + _block->getWidth() && this->getX() + this->getBoundsWidth() != _block->getX()) {
				this->setState(MarioState::STANDING);
				this->setY(_block->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				this->setComponentIdStandingOn(_block->getId());
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
	if (_goldenBrick->getState() == GOLDEN_BRICK_DISAPPEARING || _goldenBrick->getState() == GOLDEN_BRICK_DEAD) return;
	
	// When mario turning around
	if (_goldenBrick->getState() == GOLDEN_BRICK_STAYING && this->getIsTurningAround()) {
		if (get<0>(this->sweptAABBByFrame(_goldenBrick, _dt)) || this->isCollidingByFrame(_goldenBrick->getFrame())) {
			if (this->getIsFlip()) {
				if (_goldenBrick->getX() <= this->getX()
					&& _goldenBrick->getX() + _goldenBrick->getWidth() >= this->getX() - this->getLeftSpace()
					&& this->getBounds().top + this->getTailMarginTop() >= _goldenBrick->getY()
					&& this->getBounds().bottom - this->getTailMarginBottom() <= _goldenBrick->getY() + _goldenBrick->getHeight()) {
						if (_goldenBrick->getHasPButton()) {
							_goldenBrick->setState(GoldenBrickState::GOLDEN_BRICK_EMPTY);
							Grid::getInstance()->add(_goldenBrick->getPButton());
							return;
						}
						else {
							_goldenBrick->setState(GoldenBrickState::GOLDEN_BRICK_DISAPPEARING);
							return;
						}
				}
			}
			else { // -->
				if (_goldenBrick->getX() >= this->getX()
					&& _goldenBrick->getX() <= this->getX() + this->getBoundsWidth() + this->getLeftSpace()
					&& this->getBounds().top +  this->getTailMarginTop() >= _goldenBrick->getY()
					&& this->getBounds().bottom - this->getTailMarginBottom() <= _goldenBrick->getY() + _goldenBrick->getHeight()) {
						if (_goldenBrick->getHasPButton()) {
							_goldenBrick->setState(GoldenBrickState::GOLDEN_BRICK_EMPTY);
							Grid::getInstance()->add(_goldenBrick->getPButton());
							return;
						}
						else {
							_goldenBrick->setState(GoldenBrickState::GOLDEN_BRICK_DISAPPEARING);
							return;
						}
				}
			}
		}
	}


	tuple<bool, float, vector<CollisionEdge>> collisionResult;
	if (_goldenBrick->getState() == GOLDEN_BRICK_BEING_COIN) {
		collisionResult = this->sweptAABBByFrame(_goldenBrick, _dt);
	}
	else {
		collisionResult = this->sweptAABBByBounds(_goldenBrick, _dt);
	}

	if (get<0>(collisionResult) == true) {
		if (_goldenBrick->getState() == GOLDEN_BRICK_BEING_COIN) {
			_goldenBrick->setState(GoldenBrickState::GOLDEN_BRICK_DEAD);
			ScoreBoard::getInstance()->plusPoint(50);
			return;
		}

		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge
				&& this->getX() != _goldenBrick->getX() + _goldenBrick->getWidth() && this->getX() + this->getBoundsWidth() != _goldenBrick->getX()) {
				
				if (_goldenBrick->getHasPButton()) {
					_goldenBrick->setState(GoldenBrickState::GOLDEN_BRICK_EMPTY);
					Grid::getInstance()->add(_goldenBrick->getPButton());
					this->setState(MarioState::DROPPING);
					this->setY(_goldenBrick->getY() + _goldenBrick->getHeight());
					this->setVy(0);
				}
				else {
					_goldenBrick->setState(GoldenBrickState::GOLDEN_BRICK_DISAPPEARING);
				}
			}
			else if (edge == bottomEdge
				&& this->getX() != _goldenBrick->getX() + _goldenBrick->getWidth() && this->getX() + this->getBoundsWidth() != _goldenBrick->getX()) {
				this->setState(MarioState::STANDING);
				this->setY(_goldenBrick->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				this->setComponentIdStandingOn(_goldenBrick->getId());
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
		if (_goldenBrick->getState() == GOLDEN_BRICK_BEING_COIN) {
			if (this->isCollidingByFrame(_goldenBrick->getFrame())) return;
		}
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
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge
				&& this->getX() != _giftBrick->getX() + _giftBrick->getWidth() && this->getX() + this->getBoundsWidth() != _giftBrick->getX()) {
				if (_giftBrick->getState() == FULLGIFTBRICK) {
					if (_giftBrick->getGiftType() == SuperMushroomOrSuperLeaf) {
						if (this->getIsSuperMode() == false) {
							_giftBrick->setGiftType(GiftType::SuperMushroomGift);
						}
						else {
							_giftBrick->plusY(this->getVy() * _dt + (_giftBrick->getHeight() / 2));
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
				this->setState(MarioState::DROPPING);
				this->setY(_giftBrick->getY() + _giftBrick->getHeight());
				this->setVy(0);
			}
			else if (edge == bottomEdge
				&& this->getX() != _giftBrick->getX() + _giftBrick->getWidth() && this->getX() + this->getBoundsWidth() != _giftBrick->getX()) {
				this->setState(MarioState::STANDING);
				this->setY(_giftBrick->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				this->setComponentIdStandingOn(_giftBrick->getId());
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
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge
				&& this->getX() != _greenPipe->getX() + _greenPipe->getWidth() && this->getX() + this->getBoundsWidth() != _greenPipe->getX()) {
				this->setState(MarioState::DROPPING);
				this->setY(_greenPipe->getY() + _greenPipe->getHeight());
				this->setVy(0);
			}
			else if (edge == bottomEdge
				&& this->getX() != _greenPipe->getX() + _greenPipe->getWidth() && this->getX() + this->getBoundsWidth() != _greenPipe->getX()) {
				this->setState(MarioState::STANDING);
				this->setY(_greenPipe->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				this->setComponentIdStandingOn(_greenPipe->getId());
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
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
		|| this->getIsFlashMode()) {
		return;
	}

	if (_goomba->getState() == TRAMPLED_GOOMBA
		|| _goomba->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| _goomba->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| _goomba->getState() == DEAD_GOOMBA) {
		return;
	}


	// When mario turning around
	if (this->getIsTurningAround()) {
		if (get<0>(this->sweptAABBByFrame(_goomba, _dt)) || this->isCollidingByFrame(_goomba->getFrame())) {
			if (this->getIsFlip()) { // <--
				if (_goomba->getX() <= this->getX()
					&& _goomba->getX() + _goomba->getWidth() >= this->getX() - this->getLeftSpace()
					&& this->getBounds().top + this->getTailMarginTop() >= _goomba->getY()
					&& this->getBounds().bottom - this->getTailMarginBottom() <= _goomba->getY() + _goomba->getHeight()) {
					_goomba->setState(GoombaState::THROWN_LEFT_AWAY_GOOMBA);

					ScoreBoard::getInstance()->plusPoint(_goomba->getDefaultPoint());
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_goomba->getDefaultPoint(), _goomba->getX(), _goomba->getY())));
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), _goomba->getX(), _goomba->getY())));
					return;
				}
			}
			else { // -->
				if (_goomba->getX() >= this->getX()
					&& _goomba->getX() <= this->getX() + this->getBoundsWidth() + this->getLeftSpace()
					&& this->getBounds().top + this->getTailMarginTop() >= _goomba->getY()
					&& this->getBounds().bottom - this->getTailMarginBottom() <= _goomba->getY() + _goomba->getHeight()) {
					_goomba->setState(GoombaState::THROWN_RIGHT_AWAY_GOOMBA);


					ScoreBoard::getInstance()->plusPoint(_goomba->getDefaultPoint());
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_goomba->getDefaultPoint(), _goomba->getX(), _goomba->getY())));
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), _goomba->getX(), _goomba->getY())));
					return;
				}
			}
		}
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_goomba, _dt);

	/*if (_goomba->getState() == GOOMBA_FLYING_LEFT || _goomba->getState() == GOOMBA_FLYING_RIGHT || _goomba->getState() == GOOMBA_DROPPING_LEFT || _goomba->getState() == GOOMBA_DROPPING_RIGHT) {
		_goomba->setVy(_goomba->getStoredVy());
	}*/

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == bottomEdge && this->getState() == DROPPING) {
			//this->plusY(get<1>(collisionResult) * this->getVy() + _goomba->getHeight() / 4);
			this->setState(MarioState::JUMPING);

			if (_goomba->getIsFlyingMode()) {
				if (_goomba->getState() == GOOMBA_FLYING_LEFT || _goomba->getState() == GOOMBA_POPPING_LEFT) {
					//_goomba->plusY(2 * get<1>(collisionResult) * abs(this->getVy()));
					_goomba->setIsFlyingMode(false);
					_goomba->setState(GoombaState::GOOMBA_DROPPING_LEFT);
				}
				else if (_goomba->getState() == GOOMBA_FLYING_RIGHT || _goomba->getState() == GOOMBA_POPPING_RIGHT) {
					//_goomba->plusY(2 * get<1>(collisionResult) * abs(this->getVy()));
					_goomba->setIsFlyingMode(false);
					_goomba->setState(GoombaState::GOOMBA_DROPPING_RIGHT);
				}
				else if (_goomba->getState() == GOOMBA_MOVING_LEFT) {
					_goomba->setIsFlyingMode(false);
					_goomba->setState(GoombaState::GOOMBA_MOVING_LEFT);
				}
				else if (_goomba->getState() == GOOMBA_MOVING_RIGHT) {
					_goomba->setIsFlyingMode(false);
					_goomba->setState(GoombaState::GOOMBA_MOVING_RIGHT);
				}
			}
			else {
				AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_goomba->getDefaultPoint() * _goomba->getPointCoef(), _goomba->getX(), _goomba->getY())));
				_goomba->setState(GoombaState::TRAMPLED_GOOMBA);
			}


			// Calculate points
			this->increasePointCoef();
			_goomba->setPointCoef(this->getPointCoef());
			ScoreBoard::getInstance()->plusPoint(_goomba->getDefaultPoint() * _goomba->getPointCoef());
		}
		else if (edge == leftEdge) {
			_goomba->plusX(2 * get<1>(collisionResult) * _goomba->getVx());
			this->plusX(get<1>(collisionResult) * this->getVx());
			this->setState(MarioState::DIE);
		}
		else if (edge == rightEdge) {
			_goomba->plusX(2 * get<1>(collisionResult) * _goomba->getVx());
			this->plusX(get<1>(collisionResult) * this->getVx());
			this->setState(MarioState::DIE);
		}
		else if (edge == topEdge) {
			_goomba->plusX(2 * get<1>(collisionResult) * _goomba->getVx());
			_goomba->plusY(2 * get<1>(collisionResult) * _goomba->getVy());
			//this->plusY(get<1>(collisionResult) * this->getVy());
			this->setState(MarioState::DIE);
		}
	}
	else if (this->isCollidingByBounds(_goomba->getBounds())) {
		if (this->getState() == WALKING || this->getState() == STANDING) {
			this->setState(MarioState::DIE);
		}
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
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
		|| this->getIsFlashMode()) {
		return;
	}

	// When mario turning around
	if (this->getIsTurningAround()) {
		if (get<0>(this->sweptAABBByFrame(_koopa, _dt)) || this->isCollidingByFrame(_koopa->getFrame())) {
			if (this->getIsFlip()) { // <--
				if (_koopa->getX() <= this->getX()
					&& _koopa->getX() + _koopa->getWidth() >= this->getX() - this->getLeftSpace()
					&& this->getBounds().top + this->getTailMarginTop() >= _koopa->getY()
					&& this->getBounds().bottom - this->getTailMarginBottom() <= _koopa->getY() + _koopa->getHeight()) {
					if (_koopa->getState() != KOOPA_THROWN_LEFT_TO_SHINKAGE) {
						_koopa->setState(KoopaState::KOOPA_THROWN_LEFT_TO_SHINKAGE);

						AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), _koopa->getX(), _koopa->getY())));
						return;
					}
				}
			}
			else { // -->
				if (_koopa->getX() >= this->getX()
					&& _koopa->getX() <= this->getX() + this->getBoundsWidth() + this->getLeftSpace()
					&& this->getBounds().top + this->getTailMarginTop() >= _koopa->getY()
					&& this->getBounds().bottom - this->getTailMarginBottom() <= _koopa->getY() + _koopa->getHeight()) {
					if (_koopa->getState() != KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
						_koopa->setState(KoopaState::KOOPA_THROWN_RIGHT_TO_SHINKAGE);

						AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), _koopa->getX(), _koopa->getY())));
						return;
					}
				}
			}
		}
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_koopa, _dt);

	/*if (_koopa->getState() == KOOPA_FLYING_LEFT || _koopa->getState() == KOOPA_FLYING_RIGHT || _koopa->getState() == KOOPA_DROPPING_LEFT || _koopa->getState() == KOOPA_DROPPING_RIGHT) {
		_koopa->setVy(_koopa->getStoredVy());
	}*/

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];
		if (edge == leftEdge) {
			if (_koopa->getState() == KOOPA_SHRINKAGE || _koopa->getState() == KOOPA_SHRINKAGE_SHAKING) {
				_koopa->plusX(this->getVx() * _dt - (this->getBoundsWidth() / 2));
				_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
				//this->plusX(get<1>(collisionResult) * this->getVx());
			}

			else if (_koopa->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE
				|| _koopa->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				float centerMario = this->getX() + this->getBoundsWidth() / 2;
				float centerKoopa = _koopa->getX() + _koopa->getWidth() / 2;

				if (centerMario >= centerKoopa) {
					_koopa->plusX(this->getVx() * get<1>(collisionResult));
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
					_koopa->plusX(2 * this->getVx() * _dt);
				}
				else {
					_koopa->plusX(this->getVx() * get<1>(collisionResult));
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
					_koopa->plusX(2 * this->getVx() * _dt);
				}
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
			else if (_koopa->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE
				|| _koopa->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				float centerMario = this->getX() + this->getBoundsWidth() / 2;
				float centerKoopa = _koopa->getX() + _koopa->getWidth() / 2;

				if (centerMario >= centerKoopa) {
					_koopa->plusX(this->getVx() * get<1>(collisionResult));
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
					_koopa->plusX(4 * this->getVx() * _dt);
				}
				else {
					_koopa->plusX(this->getVx() * get<1>(collisionResult));
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
					_koopa->plusX(4 * this->getVx() * _dt);
				}
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
			if (_koopa->getState() == KOOPA_SHRINKAGE
				|| _koopa->getState() == KOOPA_SHRINKAGE_SHAKING) {
				float centerMario = this->getX() + this->getBoundsWidth() / 2;
				float centerKoopa = _koopa->getX() + _koopa->getWidth() / 2;

				if (centerMario >= centerKoopa) {
					_koopa->plusX(this->getVx() * get<1>(collisionResult));
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_LEFT);
					_koopa->plusX(4 * this->getVx() * _dt);
				}
				else {
					_koopa->plusX(this->getVx() * get<1>(collisionResult));
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_MOVING_RIGHT);
					_koopa->plusX(4 * this->getVx() * _dt);
				}
			}
			else if (_koopa->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE
				|| _koopa->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				float centerMario = this->getX() + this->getBoundsWidth() / 2;
				float centerKoopa = _koopa->getX() + _koopa->getWidth() / 2;

				if (centerMario >= centerKoopa) {
					_koopa->plusX(this->getVx() * get<1>(collisionResult));
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
					_koopa->plusX(4 * this->getVx() * _dt);
				}
				else {
					_koopa->plusX(this->getVx() * get<1>(collisionResult));
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
					_koopa->plusX(4 * this->getVx() * _dt);
				}
			}
			else {
				_koopa->plusX(get<1>(collisionResult) * _koopa->getVx());
				_koopa->plusY(get<1>(collisionResult) * _koopa->getVy());

				this->plusX(get<1>(collisionResult) * this->getVx());
				this->plusY(get<1>(collisionResult) * this->getVy());
				this->setState(MarioState::DIE);
			}
		}
		else if (edge == bottomEdge && this->getState() == DROPPING) {
			//this->plusY(get<1>(collisionResult) * this->getVy() + _koopa->getHeight() / 4);
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
			else if (_koopa->getState() == KOOPA_THROWN_LEFT_TO_SHINKAGE
				|| _koopa->getState() == KOOPA_THROWN_RIGHT_TO_SHINKAGE) {
				float centerMario = this->getX() + this->getBoundsWidth() / 2;
				float centerKoopa = _koopa->getX() + _koopa->getWidth() / 2;

				if (centerMario >= centerKoopa) {
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
				}
				else {
					_koopa->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
				}
			}
			else if (_koopa->getState() == KOOPA_FLYING_LEFT) {
				//_koopa->plusY(2 * get<1>(collisionResult) * abs(this->getVy()));
				_koopa->setState(KoopaState::KOOPA_DROPPING_LEFT);
			}
			else if (_koopa->getState() == KOOPA_FLYING_RIGHT) {
				//_koopa->plusY(2 * get<1>(collisionResult) * abs(this->getVy()));
				_koopa->setState(KoopaState::KOOPA_DROPPING_RIGHT);
			}
			else {
				_koopa->setState(KoopaState::KOOPA_SHRINKAGE);
			}

			_koopa->setupPointAnimPosition();
		}
	}
	/*else if (this->isCollidingByBounds(_koopa->getBounds())) {
		if ((this->getState() == WALKING || this->getState() == STANDING)
			&& _koopa->getState() != KoopaState::KOOPA_THROWN_LEFT_TO_SHINKAGE
			&& _koopa->getState() != KoopaState::KOOPA_THROWN_RIGHT_TO_SHINKAGE
			&& _koopa->getState() != KoopaState::KOOPA_SHRINKAGE
			&& _koopa->getState() != KoopaState::KOOPA_SHRINKAGE_SHAKING) {
			this->setState(MarioState::DIE);
		}
	}*/
}

void Mario::handleSuperMushroomCollision(SuperMushroom* _superMushroom, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
		|| this->getIsFlashMode()) {
		return;
	}

	if (_superMushroom->getState() == SUPER_MUSHROOM_BEING_EARNED
	||_superMushroom->getState() == SUPER_MUSHROOM_DISAPPEARED) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_superMushroom, _dt);

	if (get<0>(collisionResult) == true) {
		if (_superMushroom->getIsGreenMode()) {
			ScoreBoard::getInstance()->plusMarioLife(1);
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(Animation(AnimationBundle::getInstance()->getOneUp()), _superMushroom->getX(), _superMushroom->getY())));
		}
		else {
			ScoreBoard::getInstance()->plusPoint(1000);
			this->plusX(this->getVx() * get<1>(collisionResult));
			this->plusY(this->getVy() * get<1>(collisionResult));
			if (this->getIsSuperMode() == false) {
				this->setState(MarioState::SCALING_UP);
			}
		}

		//_superMushroom->plusX(this->getVx() * get<1>(collisionResult));
		//_superMushroom->plusY(this->getVy() * get<1>(collisionResult));
		_superMushroom->setState(SuperMushroomState::SUPER_MUSHROOM_BEING_EARNED);
	}
	else if (this->isCollidingByBounds(_superMushroom->getBounds())) {
		if (_superMushroom->getIsGreenMode()) {
			ScoreBoard::getInstance()->plusMarioLife(1);
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(Animation(AnimationBundle::getInstance()->getOneUp()), _superMushroom->getX(), _superMushroom->getY())));
		}
		else {
			ScoreBoard::getInstance()->plusPoint(1000);
			if (this->getIsSuperMode() == false) {
				this->setState(MarioState::SCALING_UP);
			}
		}

		_superMushroom->setState(SuperMushroomState::SUPER_MUSHROOM_BEING_EARNED);
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
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
		|| this->getIsFlashMode()
		|| _superLeaf->getState() == SUPER_LEAF_DISAPPEARED
		|| _superLeaf->getState() == SUPER_LEAF_BEING_EARNED) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_superLeaf, _dt);

	if (get<0>(collisionResult) == true) {
		//int xPoint = _superLeaf->getX();
		//int yPoint = _superLeaf->getY();

		//AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_superLeaf->getDefaultPoints(), _superLeaf->getX(), _superLeaf->getY())));
		ScoreBoard::getInstance()->plusPoint(1000);

		_superLeaf->plusX(_superLeaf->getVx() * get<1>(collisionResult));
		_superLeaf->plusY(_superLeaf->getVy() * get<1>(collisionResult));
		_superLeaf->setState(SuperLeafState::SUPER_LEAF_BEING_EARNED);
		this->plusX(this->getVx() * get<1>(collisionResult));
		this->plusY(this->getVy() * get<1>(collisionResult));

		if (this->getIsFlyingMode() == false && this->getIsSuperMode()) {
			this->setState(MarioState::TRANSFERING_TO_FLY);
		}
		else if (this->getIsFlyingMode() == false && this->getIsSuperMode() == false) {
			this->setState(MarioState::SCALING_UP);
		}

	}
	else if (this->isCollidingByBounds(_superLeaf->getBounds())) {
		//int xPoint = _superLeaf->getX();
		//int yPoint = _superLeaf->getY();

		//AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_superLeaf->getDefaultPoints(), _superLeaf->getX(), _superLeaf->getY())));
		ScoreBoard::getInstance()->plusPoint(1000);

		_superLeaf->setState(SuperLeafState::SUPER_LEAF_BEING_EARNED);

		if (this->getIsFlyingMode() == false && this->getIsSuperMode()) {
			this->setState(MarioState::TRANSFERING_TO_FLY);
		}
		else if (this->getIsFlyingMode() == false && this->getIsSuperMode() == false) {
			this->setState(MarioState::SCALING_UP);
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
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
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
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
		|| this->getIsFlashMode()) {
		return;
	}

	if (_fireFlowerBall->getState() == FIRE_FLOWER_BALL_FLYING_STAYING) return;

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
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
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
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN) {
		return;
	}

	if (_coin->getState() == COIN_BEING_EARNED) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_coin, _dt);

	if (get<0>(collisionResult) == true) {
		_coin->setState(CoinState::COIN_BEING_EARNED);

		ScoreBoard::getInstance()->plusPoint(50);
	}
	else {
		if (this->isCollidingByBounds(_coin->getBounds())) {
			_coin->setState(CoinState::COIN_BEING_EARNED);
			ScoreBoard::getInstance()->plusPoint(50);
		}
	}
}

void Mario::handlePButtonCollision(PButton* _pButton, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN) {
		return;
	}

	if (_pButton->getState() == PBUTTON_OFF) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_pButton, _dt);

	if (get<0>(collisionResult) == true && this->isCollidingByBounds(_pButton->getBounds())) {
		_pButton->setState(PButtonState::PBUTTON_OFF);
	}
}

void Mario::handleGreenPipeDownCollision(GreenPipe* _greenPipe, int _targetId, float _leftAnchor, float _rightAnchor, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_greenPipe, _dt);
	if (get<0>(collisionResult) == true) {
		for (size_t j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge
				&& this->getX() != _greenPipe->getX() + _greenPipe->getWidth() && this->getX() + this->getBoundsWidth() != _greenPipe->getX()) {
				if (_targetId == _greenPipe->getId()
					&& this->getX() >= _leftAnchor
					&& this->getX() + this->getBoundsWidth() <= _rightAnchor
					&& this->getIsPressKeyUp()) {
					this->setY(_greenPipe->getY() + _greenPipe->getHeight());
					this->setState(MarioState::POPPING_UP_PIPE);
				}
				else {
					this->setState(MarioState::DROPPING);
					this->setY(_greenPipe->getY() + _greenPipe->getHeight());
					this->setVy(0);
				}
			}
			else if (edge == bottomEdge
				&& this->getX() != _greenPipe->getX() + _greenPipe->getWidth() && this->getX() + this->getBoundsWidth() != _greenPipe->getX()) {
				this->setState(MarioState::STANDING);
				this->setY(_greenPipe->getY() - this->getBoundsHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				this->setComponentIdStandingOn(_greenPipe->getId());
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

void Mario::handleMusicBoxCollision(MusicBox* _musicBox, float _dt)
{
	if (_musicBox->getState() != MusicBoxState::MUSIC_BOX_STAYING) return;

	if (_musicBox->getIsSpecial() && _musicBox->getIsTransparentMode()) {
		if (this->isCollidingByBounds(_musicBox->getBounds()) && this->getState() == JUMPING && this->getY() > _musicBox->getY()) {
			this->setState(MarioState::WALKING);
			this->setX(_musicBox->getX() + _musicBox->getBoundsWidth() + 1);
			_musicBox->setIsTransparentMode(false);
			_musicBox->setState(MusicBoxState::MUSIC_BOX_JUMPING_UP);
			return;
		}
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_musicBox, _dt);

	if (get<0>(collisionResult) == true) {
		//for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[0];
			if (edge == topEdge
				&& this->getX() != _musicBox->getX() + _musicBox->getWidth() && this->getX() + this->getBoundsWidth() != _musicBox->getX()) {

				if (_musicBox->getIsSpecial() && _musicBox->getIsTransparentMode()) {
					_musicBox->setIsTransparentMode(false);
				}

				this->setState(MarioState::DROPPING);
				this->setY(_musicBox->getY() + _musicBox->getHeight());
				this->setVy(0);

				_musicBox->setState(MusicBoxState::MUSIC_BOX_JUMPING_UP);
			}
			else if (edge == bottomEdge
				&& this->getX() != _musicBox->getX() + _musicBox->getWidth() && this->getX() + this->getBoundsWidth() != _musicBox->getX()) {

				if (_musicBox->getIsTransparentMode()) return;

				if (_musicBox->getIsSpecial() && this->getIsPressKeyS()) {
					this->setState(MarioState::JUMPING_UP_TO_CLOUND);
				}
				else {
					this->setState(MarioState::JUMPING);
					this->setVy(this->getVy() * float(1.2));
				}
				this->setY(_musicBox->getY() - this->getBoundsHeight());
				_musicBox->setState(MusicBoxState::MUSIC_BOX_JUMPING_DOWN);
			}
			else if (edge == leftEdge && this->getY() + this->getBoundsHeight() != _musicBox->getY()) {

				if (_musicBox->getIsTransparentMode()) return;

				this->setX(_musicBox->getX() + _musicBox->getWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge && this->getY() + this->getBoundsHeight() != _musicBox->getY()) {

				if (_musicBox->getIsTransparentMode()) return;

				this->setX(_musicBox->getX() - this->getBoundsWidth());
				this->setSubState(MarioSubState::PUSHING);
			}
		//}
	}
}

void Mario::handleBoomerangBroCollision(BoomerangBro* _boomerangBro, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
		|| this->getIsFlashMode()) {
		return;
	}

	if (_boomerangBro->getState() == BOOMERANG_BRO_BEING_DEAD) return;


	// When mario turning around
	if (this->getIsTurningAround()) {
		if (get<0>(this->sweptAABBByFrame(_boomerangBro, _dt)) || this->isCollidingByFrame(_boomerangBro->getFrame())) {
			if (this->getIsFlip()) { // <--
				if (_boomerangBro->getX() <= this->getX()
					&& _boomerangBro->getX() + _boomerangBro->getWidth() >= this->getX() - this->getLeftSpace()
					&& this->getBounds().top + this->getTailMarginTop() >= _boomerangBro->getY()
					&& this->getBounds().bottom - this->getTailMarginBottom() <= _boomerangBro->getY() + _boomerangBro->getHeight()) {
					_boomerangBro->setState(BoomerangBroState::BOOMERANG_BRO_BEING_DEAD);

					ScoreBoard::getInstance()->plusPoint(100);
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(100, _boomerangBro->getX(), _boomerangBro->getY())));
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), _boomerangBro->getX(), _boomerangBro->getY())));
					return;
				}
			}
			else { // -->
				if (_boomerangBro->getX() >= this->getX()
					&& _boomerangBro->getX() <= this->getX() + this->getBoundsWidth() + this->getLeftSpace()
					&& this->getBounds().top + this->getTailMarginTop() >= _boomerangBro->getY()
					&& this->getBounds().bottom - this->getTailMarginBottom() <= _boomerangBro->getY() + _boomerangBro->getHeight()) {
					_boomerangBro->setState(BoomerangBroState::BOOMERANG_BRO_BEING_DEAD);

					ScoreBoard::getInstance()->plusPoint(100);
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(100, _boomerangBro->getX(), _boomerangBro->getY())));
					AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFlashLight()), _boomerangBro->getX(), _boomerangBro->getY())));
					return;
				}
			}
		}
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_boomerangBro, _dt);

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];

		if (edge == bottomEdge) {
			this->setState(MarioState::JUMPING);
			_boomerangBro->setState(BoomerangBroState::BOOMERANG_BRO_BEING_DEAD);
			ScoreBoard::getInstance()->plusPoint(1000);
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(Animation(AnimationBundle::getInstance()->get1000Points()), _boomerangBro->getX(), _boomerangBro->getY())));
		}
		else {
			this->setState(MarioState::DIE);
		}
	}
	else {
		if (this->isCollidingByBounds(_boomerangBro->getBounds())) {
			this->setState(MarioState::DIE);
		}
	}
}

void Mario::handleBoomerangCollision(Boomerang* _boomerang, float _dt)
{
	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
		|| this->getIsFlashMode()) {
		return;
	}

	if (_boomerang->getState() == BOOMERANG_STAYING) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_boomerang, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_boomerang->getBounds())) {
		this->setState(MarioState::DIE);
	}
}

void Mario::handleBossCollision(Boss* _boss, float _dt)
{

	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
		|| this->getIsFlashMode()) {
		return;
	}

	if (_boss->getState() == BOSS_THROWING_LEFT_AWAT || _boss->getState() == BOSS_THROWING_RIGHT_AWAY || _boss->getState() == BOSS_TRAMPLED || _boss->getState() == BOSS_DEAD) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_boss, _dt);

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];

		if (edge == bottomEdge) {
			this->setState(MarioState::JUMPING);
			
			if (_boss->getIsFlyingMode()) {
				_boss->setIsFlyingMode(false);

				if (_boss->getState() == BOSS_DROPPING_LEFT) {
					_boss->setState(BossState::BOSS_DROPPING_LEFT);
				}
				else if (_boss->getState() == BOSS_DROPPING_RIGHT) {
					_boss->setState(BossState::BOSS_DROPPING_RIGHT);
				}
				else if (_boss->getState() == BOSS_FLYING_LEFT) {
					_boss->setState(BossState::BOSS_DROPPING_LEFT);
				}
				else if (_boss->getState() == BOSS_FLYING_RIGHT) {
					_boss->setState(BossState::BOSS_DROPPING_RIGHT);
				}
				else if (_boss->getState() == BOSS_FLYING_TOP_LEFT) {
					_boss->setState(BossState::BOSS_DROPPING_LEFT);
				}
				else if (_boss->getState() == BOSS_FLYING_TOP_RIGHT) {
					_boss->setState(BossState::BOSS_DROPPING_RIGHT);
				}
				else if (_boss->getState() == BOSS_MOVING_LEFT) {
					_boss->setState(BossState::BOSS_MOVING_LEFT);
				}
				else if (_boss->getState() == BOSS_MOVING_RIGHT) {
					_boss->setState(BossState::BOSS_MOVING_RIGHT);
				}
			}
			else {
				_boss->setState(BossState::BOSS_TRAMPLED);
				AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_boss->getDefaultPoint() * _boss->getPointCoef(), _boss->getX(), _boss->getY())));
			}

			// Calculate points
			this->increasePointCoef();
			_boss->setPointCoef(this->getPointCoef());
			ScoreBoard::getInstance()->plusPoint(_boss->getDefaultPoint()* _boss->getPointCoef());
		}
		else {
			_boss->plusX(_boss->getVx() * get<1>(collisionResult));
			this->setState(MarioState::DIE);
		}
	}
}

void Mario::handleBombCollision(Bomb* _bomb, float _dt)
{

	if (this->getState() == DIE
		|| this->getState() == DIE_JUMPING
		|| this->getState() == DIE_DROPPING
		|| this->getState() == SCALING_UP
		|| this->getState() == SCALING_DOWN
		|| this->getState() == TRANSFERING_TO_FLY
		|| this->getState() == DROPPING_DOWN_PIPE
		|| this->getState() == POPPING_UP_PIPE
		|| this->getState() == JUMPING_UP_TO_CLOUND
		|| this->getState() == DROPPING_DOWN_WIN
		|| this->getState() == MOVING_RIGHT_WIN
		|| this->getIsFlashMode()) {
		return;
	}

	if (_bomb->getState() == BOMB_STAYING) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_bomb, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_bomb->getBounds())) {
		_bomb->setState(BombState::BOMB_STAYING);
		this->increaseBombAttached();
	}
}
