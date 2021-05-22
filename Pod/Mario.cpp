#include "Mario.h"

void Mario::setUpAnimations()
{
	this->animations = new vector<Animation*>();

	this->animations->push_back(new Animation(0, 0, 2, FilePath::getInstance()->mario_standing));
	this->animations->push_back(new Animation(0, 0, 2, FilePath::getInstance()->mario_running));
}

Mario::Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->state = _state;
	this->setState(_state);
	setUpAnimations();
	updateCurrentAnimation(this->getState());
}

Mario::Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : Component(_position, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_position, _vx, _vy, _limitX, _limitY);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->state = _state;
	this->setState(_state);
	setUpAnimations();
	updateCurrentAnimation(this->getState());
}

Mario::~Mario()
{
	Component::~Component();
	delete& texture;
	delete& state;
	delete& isFlip;

	for (int i = 0; i < this->animations->size(); ++i) {
		delete this->animations->at(i);
	}
	delete currentAnimation;
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

void Mario::Update(float _dt)
{
	if (currentAnimation == NULL) {
		return;
	}

	this->updateCurrentAnimation(this->state);
	this->currentAnimation->Update(_dt);
	this->plusX(this->getCurrentVx() * _dt);
	this->plusY(this->getCurrentVy() * _dt);
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

	float translateY = -this->currentAnimation->getCurrentFrameHeight();
	if (this->getY() > camera->getHeight() / 2) {
		translateY = -(camera->getY() + this->currentAnimation->getCurrentFrameHeight());
	}
	this->currentAnimation->Draw(this->texture, this->getPosition(), D3DXVECTOR2(translateX, translateY), D3DCOLOR_XRGB(255, 255, 255), this->isFlip);
}

void Mario::setState(MarioState _state)
{
	this->state = _state;
	if (_state == STANDING_RIGHT || _state == WALKING_RIGHT) {
		this->isFlip = false;
	}
	else {
		this->isFlip = true;
	}
}

void Mario::updateCurrentAnimation(MarioState _state)
{
	switch (_state)
	{
	case DROPPING:
		break;
	case STANDING_LEFT:
		currentAnimation = this->animations->at(0);
		break;
	case STANDING_RIGHT:
		currentAnimation = this->animations->at(0);
		break;
	case JUMPING:
		break;
	case WALKING_LEFT:
		currentAnimation = this->animations->at(1);
		break;
	case WALKING_RIGHT:
		currentAnimation = this->animations->at(1);
		break;
	default:
		break;
	}
}

void Mario::onKeyUp()
{
	switch (this->getState())
	{
	case WALKING_LEFT:
		this->setState(MarioState::STANDING_LEFT);
		break;
	case WALKING_RIGHT:
		this->setState(MarioState::STANDING_RIGHT);
		break;
	default:
		break;
	}
	this->setCurrentVx(0);
	this->setCurrentVy(0);
}

void Mario::onKeyDown(KeyType _keyType)
{
	switch (_keyType)
	{
	case KeyType::up:
		this->setCurrentVy(-this->getVy());
		break;
	case KeyType::down:
		this->setCurrentVy(this->getVy());
		break;
	case KeyType::left:
		if (this->state != WALKING_LEFT) { // increase performance 1
			this->setState(MarioState::WALKING_LEFT);
		}
		this->setCurrentVx(-this->getVx());
		break;
	case KeyType::right:
		if (this->state != WALKING_RIGHT) {
			this->setState(MarioState::WALKING_RIGHT);
		}
		this->setCurrentVx(this->getVx());
		break;
	default:
		break;
	}
}
