#include "Mario.h"
#include "Goomba.h"

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

MarioSubState Mario::getSubState()
{
	return this->subState;
}

MarioState Mario::getState()
{
	return this->state;
}

MarioState Mario::getPressureState()
{
	return this->pressureState;
}

bool Mario::getIsFlip()
{
	return this->isFlip;
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

void Mario::Update(float _dt)
{
	if (currentAnimation == NULL) {
		return;
	}
	// Update animation frame
	this->currentAnimation->Update(_dt);

	if (this->getState() == SCALING_UP) {
		if (this->currentAnimation->getCurrentIndexFrame() == this->currentAnimation->getTotalFrames() - 1
			&& this->currentAnimation->getAnimCount() >= this->currentAnimation->getAnimDelay()) {
			this->setState(this->getPressureState());
		}
	}

	// Change from DIE to DIE_JUMPING
	if (this->getState() == DIE) {
		if (this->currentAnimation->getCurrentIndexFrame() == this->currentAnimation->getTotalFrames() - 1
		&& this->currentAnimation->getAnimCount() >= this->currentAnimation->getAnimDelay()) {
			this->setState(MarioState::DIE_JUMPING);
		}
	}

	// Update position, velocity
	this->updateVelocity();
	if (this->getX() + round(this->getVx() * _dt) >= 0 && this->getX() + this->getWidth() + round(this->getVx() * _dt) <= this->getLimitX()) {
		this->plusX(round(this->getVx() * _dt));
	}
	this->plusY(round(this->getVy() * _dt));

	// Navigate to WorldVC when Mario drop out of map to far
	if (this->getY() >= this->getLimitY() + 200) {
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

	this->currentAnimation->DrawWithoutCamera(this->texture, this->getPosition(), D3DXVECTOR2(translateX, translateY), this->getIsFlip(), D3DCOLOR_XRGB(255, 255, 255));

	if (debugMode == Setting::getInstance()->getDebugMode()) {
		Drawing::getInstance()->drawDebugBox(this->getFrame(), NULL, this->getPosition(), D3DXVECTOR2(translateX, translateY), false, D3DCOLOR_ARGB(128, 255, 255, 255));
	}
}

void Mario::setIsFlip(bool _isFlip)
{
	this->isFlip = _isFlip;
}

void Mario::setState(MarioState _state)
{
 	if (currentAnimation != NULL) {
		this->oldFrameWidth = this->currentAnimation->getCurrentFrameWidth();
		this->oldFrameHeight = this->currentAnimation->getCurrentFrameHeight();
	}

	switch (_state)
	{
	case STANDING:
		if (this->getState() != STANDING || this->currentAnimation == NULL) {
			if (this->getIsSuperMode()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioStanding());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioStanding());
			}
			this->setTargetVx(0);
			this->setTargetVy(0);
			this->setAccelerationY(0);
			this->setVy(0);

			if (this->getVx() > this->getTargetVx()) {
				this->setAccelerationX(-0.6);
			}
			else if (this->getVx() < this->getTargetVx()) {
				this->setAccelerationX(0.6);
			}
			else {
				this->setAccelerationX(0);
			}
		}
		break;
	case WALKING:
		if (this->getState() != WALKING || this->currentAnimation == NULL) {
			if (this->getIsSuperMode()) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioWalking());
			}
			else {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioWalking());
			}
		}
		
		break;
	case JUMPING:
		if (this->getState() != JUMPING || this->currentAnimation == NULL) {
			if (this->getState() != DROPPING) {
				if (this->getIsSuperMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioJumping());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioJumping());
				}
			}
			this->setTargetVy(0);
			this->setVy(this->getIsSuperMode() ? -4.4 : -4.0);
			this->setAccelerationY(0.11);
		}

		break;
	case DROPPING:
		if (this->getState() != DROPPING || this->currentAnimation == NULL) {
			if (this->getState() != JUMPING) {
				if (this->getIsSuperMode()) {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getSuperMarioDropping());
				}
				else {
					this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDropping());
				}
			}
			this->setTargetVy(6);
			this->setAccelerationY(0.25);
		}
		break;
	case DIE:
		if (this->getState() != DIE || this->currentAnimation == NULL) {
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDie());
			this->setTargetVx(0);
			this->setTargetVy(0);
			this->setAccelerationX(0);
			this->setAccelerationY(0);
			this->setVx(0);
			this->setVy(0);
		}
		break;
	case DIE_JUMPING:
		if (this->getState() != DIE_JUMPING || this->currentAnimation == NULL) {
			if (this->getState() != DIE) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDie());
			}
			this->setTargetVx(0);
			this->setTargetVy(0);
			this->setAccelerationX(0);
			this->setAccelerationY(0.11);
			this->setVx(0);
			this->setVy(-4.4);
		}
		break;
	case DIE_DROPPING:
		if (this->getState() != DIE_DROPPING || this->currentAnimation == NULL) {
			if (this->getState() != DIE && this->getState() != DIE_JUMPING) {
				this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioDie());
			}
			this->setTargetVx(0);
			this->setTargetVy(6);
			this->setAccelerationX(0);
			this->setAccelerationY(0.34);
			this->setVx(0);
			this->setVy(0);
		}
		break;
	case SCALING_UP:
		if (this->getState() != SCALING_UP || this->currentAnimation == NULL) {
			// Store old state to pressureState variable
			this->setIsSuperMode(true);
			this->setPressureState(MarioState(this->getState()));
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioScalingUp());
			this->setTargetVx(0);
			this->setTargetVy(0);
			this->setAccelerationX(0);
			this->setAccelerationY(0);
			this->setVx(0);
			this->setVy(0);
		}
		break;
	case SCALING_DOWN:
		if (this->getState() != SCALING_DOWN || this->currentAnimation == NULL) {
			// Store old state to pressureState variable
			this->setIsSuperMode(false);
			this->setPressureState(MarioState(this->getState()));
			this->currentAnimation = new Animation(AnimationBundle::getInstance()->getMarioScalingDown());
		}
		break;
	default:
		break;
	}

	this->state = _state;

	this->newFrameWidth = this->currentAnimation->getCurrentFrameWidth();
	this->newFrameHeight = this->currentAnimation->getCurrentFrameHeight();

	if (oldFrameWidth != newFrameWidth) {
		this->plusX(oldFrameWidth - newFrameWidth);

	}
	if (oldFrameHeight != newFrameHeight) {
		this->plusY(oldFrameHeight - newFrameHeight);
	}
}

void Mario::setPressureState(MarioState _pressureState)
{
	this->pressureState = _pressureState;
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

void Mario::setIsSuperMode(bool _isSuperMode)
{
	this->isSuperMode = _isSuperMode;
}

void Mario::updateVelocity()
{
	if (this->getTargetVx() > 0) {
		if (this->getVx() + this->getAccelerationX() <= this->getTargetVx()) {
			this->plusVx(this->getAccelerationX());
		}
	}
	else if (this->getTargetVx() < 0) {
		if (this->getVx() + this->getAccelerationX() >= this->getTargetVx()) {
			this->plusVx(this->getAccelerationX());
		}
	}
	else { // = 0
		if (this->getIsFlip() == false) { // -->
			if (this->getVx() + this->getAccelerationX() > 0) {
				this->plusVx(this->getAccelerationX());
			}
			else {
				this->setVx(0);
			}
		}
		else { // <--
			if (this->getVx() + this->getAccelerationX() < 0) {
				this->plusVx(this->getAccelerationX());
			}
			else {
				this->setVx(0);
			}
		}
	}

	if (this->getTargetVy() > 0) {
		if (this->getVy() + this->getAccelerationY() <= this->getTargetVy()) {
			this->plusVy(this->getAccelerationY());
		}
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

void Mario::onKeyUp()
{
	if (this->getState() == WALKING) {
		this->setState(MarioState::STANDING);
	}
	else if (this->getState() == DROPPING) {
		if (this->getVx() < 0) {
			this->setAccelerationX(0.2);
		}
		else if (this->getVx() > 0) {
			this->setAccelerationX(-0.2);
		}
		if (this->getTargetVx() != 0) {
			this->setTargetVx(0);
		}
	}
}

void Mario::onKeyUp(vector<KeyType> _keyTypes)
{
	for (int i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == KeyType::space) {
			if (this->getState() == JUMPING) {
				startdrop = this->getY();
				this->setState(MarioState::DROPPING);
			}
		}
		else if (_keyTypes[i] == KeyType::right) {
			if (this->getSubState() == PUSHING) {
				this->setSubState(MarioSubState::NONE);
			}
		}
		else if (_keyTypes[i] == KeyType::left) {
			if (this->getSubState() == PUSHING) {
				this->setSubState(MarioSubState::NONE);
			}
		}
	}
}

void Mario::onKeyDown(vector<KeyType> _keyTypes)
{
	bool hasKeyRight = false;
	bool hasKeyLeft = false;

	for (int i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == KeyType::right) {
			if (this->getSubState() == PUSHING) {
				continue;
			}
			hasKeyRight = true;

			if (!hasKeyLeft) {
				this->setIsFlip(false);
				if (this->getState() == DROPPING) {
					this->setTargetVx(1.2);
				}
				else {
					this->setTargetVx(1.6);
				}
				this->setAccelerationX(0.4);
			}
			else {
				this->setTargetVx(0);
				if (this->getVx() > this->getTargetVx()) {
					this->setAccelerationX(-0.2);
				}
				else if (this->getVx() < this->getTargetVx()) {
					this->setAccelerationX(0.2);
				}
				else {
					this->setAccelerationX(0);
				}
			}
		}
		else if (_keyTypes[i] == KeyType::left) {
			if (this->getSubState() == PUSHING) {
				continue;
			}
			hasKeyLeft = true;

			if (!hasKeyRight) {
				this->setIsFlip(true);
				if (this->getState() == DROPPING) {
					this->setTargetVx(-1.2);
				}
				else {
					this->setTargetVx(-1.6);
				}
				this->setAccelerationX(-0.4);
			}
			else {
				this->setTargetVx(0);
				if (this->getVx() > this->getTargetVx()) {
					this->setAccelerationX(-0.2);
				}
				else if (this->getVx() < this->getTargetVx()) {
					this->setAccelerationX(0.2);
				}
				else {
					this->setAccelerationX(0);
				}
			}
		}
		else if (_keyTypes[i] == KeyType::space) {
			if (this->getState() == DROPPING) {
				return;
			}
			if (this->getState() == STANDING || this->getState() == WALKING) {
				this->setState(MarioState::JUMPING);
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

void Mario::loadInfo(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);
	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setLimitX(stof(v[2]));
	this->setLimitY(stof(v[3]));
	//this->setState(Tool::getMarioStateFromString(v[4]));
}

void Mario::handleGroundCollision(Ground* _ground, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_ground, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge) {
				this->setState(MarioState::DROPPING);
				this->setY(_ground->getFrame().bottom);
				this->setVy(0);
				//this->setIsStandOnSurface(true);
				//this->componentIdStanded = _ground->getId();
			}
			else if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_ground->getY() - this->getHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				//this->componentIdStanded = _ground->getId();
			}
			else if (edge == leftEdge) {
				this->setX(_ground->getFrame().right + Setting::getInstance()->getCollisionSafeSpace());
				this->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge) {
				this->setX(_ground->getFrame().left - this->getWidth() - Setting::getInstance()->getCollisionSafeSpace());
				this->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_ground->getX() <= this->getFrame().right && this->getFrame().right <= _ground->getFrame().right)
					|| (_ground->getX() <= this->getX() && this->getX() <= _ground->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getFrame().bottom == _ground->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleBlockCollision(Block* _block, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_block, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_block->getY() - this->getHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				//this->componentIdStanded = _block->getId();
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_block->getX() <= this->getFrame().right && this->getFrame().right <= _block->getFrame().right)
					|| (_block->getX() <= this->getX() && this->getX() <= _block->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getFrame().bottom == _block->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleGoldenBrickCollision(GoldenBrick* _goldenBrick, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_goldenBrick, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge) {
				this->setState(MarioState::DROPPING);
				this->setY(_goldenBrick->getFrame().bottom);
				this->setVy(0);
				//this->setIsStandOnSurface(true);
				//this->componentIdStanded = _goldenBrick->getId();
			}
			else if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_goldenBrick->getY() - this->getHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				//this->componentIdStanded = _goldenBrick->getId();
			}
			else if (edge == leftEdge) {
				this->setX(_goldenBrick->getFrame().right + Setting::getInstance()->getCollisionSafeSpace());
				this->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge) {
				this->setX(_goldenBrick->getFrame().left - this->getWidth() - Setting::getInstance()->getCollisionSafeSpace());
				this->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_goldenBrick->getX() <= this->getFrame().right && this->getFrame().right <= _goldenBrick->getFrame().right)
					|| (_goldenBrick->getX() <= this->getX() && this->getX() <= _goldenBrick->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getFrame().bottom == _goldenBrick->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleGiftBrickCollision(GiftBrick* _goldenBrick, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_goldenBrick, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge) {
				this->setState(MarioState::DROPPING);
				this->setY(_goldenBrick->getFrame().bottom);
				this->setVy(0);
				//this->setIsStandOnSurface(true);
				//this->componentIdStanded = _goldenBrick->getId();
				if (_goldenBrick->getState() == FULLGIFTBRICK) {
					_goldenBrick->setState(GiftBrickState::POPUPGIFTBRICK);
					if (_goldenBrick->getGiftType() == Point100Gift) {
						ScoreBoard::getInstance()->plusCoin(1);
						ScoreBoard::getInstance()->plusPoint(100);
					}
				}
			}
			else if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_goldenBrick->getY() - this->getHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				//this->componentIdStanded = _goldenBrick->getId();
			}
			else if (edge == leftEdge && (this->getState() == JUMPING || this->getState() == DROPPING)) {
				this->setX(_goldenBrick->getFrame().right + Setting::getInstance()->getCollisionSafeSpace());
				this->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge && (this->getState() == JUMPING || this->getState() == DROPPING)) {
				this->setX(_goldenBrick->getFrame().left - this->getWidth() - Setting::getInstance()->getCollisionSafeSpace());
				this->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_goldenBrick->getX() <= this->getFrame().right && this->getFrame().right <= _goldenBrick->getFrame().right)
					|| (_goldenBrick->getX() <= this->getX() && this->getX() <= _goldenBrick->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getFrame().bottom == _goldenBrick->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleGreenPipeCollision(GreenPipe* _greenPipe, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_greenPipe, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == topEdge) {
				this->setState(MarioState::DROPPING);
				this->setY(_greenPipe->getFrame().bottom);
				this->setVy(0);
				//this->setIsStandOnSurface(true);
				//this->componentIdStanded = _greenPipe->getId();
			}
			else if (edge == bottomEdge) {
				this->setState(MarioState::STANDING);
				this->setY(_greenPipe->getY() - this->getHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->setIsStandOnSurface(true);
				//this->componentIdStanded = _greenPipe->getId();
			}
			else if (edge == leftEdge) {
				this->setX(_greenPipe->getFrame().right + Setting::getInstance()->getCollisionSafeSpace());
				this->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge) {
				this->setX(_greenPipe->getFrame().left - this->getWidth() - Setting::getInstance()->getCollisionSafeSpace());
				this->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_greenPipe->getX() <= this->getFrame().right && this->getFrame().right <= _greenPipe->getFrame().right)
					|| (_greenPipe->getX() <= this->getX() && this->getX() <= _greenPipe->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getFrame().bottom == _greenPipe->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void Mario::handleGoombaCollision(Goomba* _goomba, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_goomba, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setState(MarioState::JUMPING);
				this->plusY(get<1>(collisionResult) * _dt + (_goomba->getHeight() / 2));
				_goomba->setState(GoombaState::TRAMPLED_GOOMBA);
				ScoreBoard::getInstance()->plusPoint(100);
			}
			else if (edge == leftEdge) {
				this->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * this->getVx());
				_goomba->setState(GoombaState::GOOMBA_STANDING);
			}
			else if (edge == rightEdge) {
				this->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * this->getVx());
				_goomba->setState(GoombaState::GOOMBA_STANDING);
			}
		}
	}
}

bool Mario::isCollide(Component* _component, float _dt)
{
	return get<0>(this->sweptAABBByBounds(_component, _dt));
}
