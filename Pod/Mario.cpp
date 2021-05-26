#include "Mario.h"

void Mario::setUpAnimations()
{
	this->animations = new vector<Animation*>();

	this->animations->push_back(new Animation(0, 0, 2, FilePath::getInstance()->mario_standing));
	this->animations->push_back(new Animation(0, 0, 2, FilePath::getInstance()->mario_running));
	this->animations->push_back(new Animation(0, 0, 2, FilePath::getInstance()->mario_jumping_dropping));
}

Mario::Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY)
{
	MainCharacter::MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY);
	setUpAnimations();
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->state = _state;
	this->setState(_state);
}

Mario::Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : MainCharacter(_position, _vx, _vy, _limitX, _limitY)
{
	MainCharacter::MainCharacter(_position, _vx, _vy, _limitX, _limitY);
	setUpAnimations();
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->state = _state;
	this->setState(_state);
}

Mario::~Mario()
{
	MainCharacter::~MainCharacter();
	delete& texture;
	delete& state;
	delete& isFlip;

	for (int i = 0; i < this->animations->size(); ++i) {
		delete this->animations->at(i);
	}
	delete currentAnimation;
}

Animation* Mario::getCurrentAnimation()
{
	return this->currentAnimation;
}

MarioState Mario::getState()
{
	return this->state;
}

RECT* Mario::getBounds()
{
	if (currentAnimation == NULL) {
		return NULL;
	}

	RECT* r = new RECT();
	r->top = this->getY();
	r->bottom = r->top + this->currentAnimation->getCurrentFrameHeight();
	r->left = this->getX();
	r->right = r->left + this->currentAnimation->getCurrentFrameWidth();

	return r;
}

bool Mario::getIsFlip()
{
	return this->isFlip;
}

void Mario::Update(float _dt)
{
	if (currentAnimation == NULL) {
		return;
	}
	this->currentAnimation->Update(_dt);
	this->updateVelocity();
	this->plusX(round(this->getVx() * _dt));
	this->plusY(round(this->getVy() * _dt));
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

	this->currentAnimation->Draw(this->texture, this->getPosition(), D3DXVECTOR2(translateX, translateY), this->getIsFlip(), D3DCOLOR_XRGB(255, 255, 255));
}

void Mario::setIsFlip(bool _isFlip)
{
	this->isFlip = _isFlip;
}

void Mario::setState(MarioState _state)
{
	switch (_state)
	{
	case STANDING:
		if (this->getState() != STANDING || this->currentAnimation == NULL) {
			this->currentAnimation = this->animations->at(0);
			this->setTargetVx(0);
			this->setTargetVy(0);
			this->setAccelerationY(0);
			this->setVy(0);
			if (this->getState() == WALKING) {
				int a = 0;
			}

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
			this->currentAnimation = this->animations->at(1);
			
		}
		
		break;
	case JUMPING:
		if (this->getState() != JUMPING || this->currentAnimation == NULL) {
			this->currentAnimation = this->animations->at(2);
			this->setTargetVy(0);
			this->setVy(-5);
			this->setAccelerationY(0.2);
		}

		break;
	case DROPPING:
		if (this->getState() != DROPPING || this->currentAnimation == NULL) {
			this->currentAnimation = this->animations->at(2);
			this->setTargetVy(10);
			this->setAccelerationY(1);
		}
		break;
	default:
		break;
	}

	this->state = _state;
}

void Mario::updateVelocity()
{
	/*if (this->accelerationX > 0) {
		if (this->getVx() + this->accelerationX <= this->maxVx) {
			this->plusVx(this->accelerationX);
		}
	}
	else if (this->accelerationX < 0) {
		if (this->getVx() + this->accelerationX >= this->maxVx) {
			this->plusVx(this->accelerationX);
		}
	}

	if (this->accelerationY > 0) {
		if (this->getVy() + this->accelerationY <= this->maxVy) {
			this->plusVy(this->accelerationY);
		}
	}
	else if (this->accelerationY < 0) {
		if (this->getVy() + this->accelerationY >= this->maxVy) {
			this->plusVy(this->accelerationY);
			if (this->accelerationY >= -3) {
				int a = 0;
			}
			if (this->accelerationY <= -1) {
    				this->accelerationY += 1;
			}
			else {
				this->setState(MarioState::DROPPING);
			}
		}
	}*/

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

	/*if (abs(this->getVx()) > 10) {
		int a = 0;
	}*/

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
	}
}

void Mario::onKeyUp()
{
	if (this->getState() == WALKING) {
		this->setState(MarioState::STANDING);
	}
	else if (this->getState() == DROPPING) {
		if (this->getAccelerationX() != 0) {
			this->setAccelerationX(0);
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
				this->setState(MarioState::DROPPING);
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
			hasKeyRight = true;

			if (!hasKeyLeft) {
				this->setIsFlip(false);
				if (this->getState() == DROPPING) {
					this->setTargetVx(2);
				}
				else {
					this->setTargetVx(3);
				}
				this->setAccelerationX(0.4);
			}
			else {
				this->setTargetVx(0);
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
		}
		else if (_keyTypes[i] == KeyType::left) {
			hasKeyLeft = true;

			if (!hasKeyRight) {
				this->setIsFlip(true);
				if (this->getState() == DROPPING) {
					this->setTargetVx(-2);
				}
				else {
					this->setTargetVx(-3);
				}
				this->setAccelerationX(-0.4);
			}
			else {
				this->setTargetVx(0);
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
		}
		else if (_keyTypes[i] == KeyType::space) {
			
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
