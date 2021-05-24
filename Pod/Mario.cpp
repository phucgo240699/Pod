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
			this->accelerationX = 0;
			this->accelerationY = 0;
			this->maxVx = 0;
			this->maxVy = 0;
			this->setVx(0);
			this->setVy(0);
		}
		break;
	case WALKING:
		if (this->getState() != WALKING || this->currentAnimation == NULL) {
			this->currentAnimation = this->animations->at(1);
		}
		break;
	case DROPPING:
		if (this->getState() != DROPPING || this->currentAnimation == NULL) {
			this->currentAnimation = this->animations->at(2);
			this->accelerationY = 1;
			this->maxVy = 10;
		}
		break;
	default:
		break;
	}

	this->state = _state;
}

void Mario::updateVelocity()
{
	if (this->accelerationX > 0) {
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
		}
	}
}

void Mario::onKeyUp()
{
	if (this->getState() == WALKING) {
		this->setState(MarioState::STANDING);
	}
}

void Mario::onKeyUp(vector<KeyType> _keyTypes)
{
	for (int i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == KeyType::right) {
			if (this->getVx() > 0) {
				this->accelerationX = -1;
			}
			else if (this->getVx() < 0) {
				this->accelerationX = 1;
			}
			this->maxVx = 0;
		}
		else if (_keyTypes[i] == KeyType::left) {
			if (this->getVx() > 0) {
				this->accelerationX = -1;
			}
			else if (this->getVx() < 0) {
				this->accelerationX = 1;
			}
			this->maxVx = 0;
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
			this->maxVx = 2;
			if (!hasKeyLeft) {
				this->accelerationX = 1;
				this->setIsFlip(false);
			}
			else {
				if (this->getVx() > 0) {
					this->accelerationX = -1;
				}
				else if (this->getVx() < 0) {
					this->accelerationX = 1;
				}
			}
			if (this->getState() == STANDING) {
				this->setState(MarioState::WALKING);
			}
		}
		else if (_keyTypes[i] == KeyType::left) {
			hasKeyLeft = true;
			this->maxVx = -2;
			if (!hasKeyRight) {
				this->accelerationX = -1;
				this->setIsFlip(true);
			}
			else {
				if (this->getVx() > 0) {
					this->accelerationX = -1;
				}
				else if (this->getVx() < 0) {
					this->accelerationX = 1;
				}
			}
			if (this->getState() == STANDING) {
				this->setState(MarioState::WALKING);
			}
		}
	}
}
