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

	float translateY = -this->currentAnimation->getCurrentFrameHeight();
	if (this->getY() > camera->getHeight() / 2) {
		translateY = -(camera->getY());
	}
	this->currentAnimation->Draw(this->texture, this->getPosition(), D3DXVECTOR2(translateX, translateY), D3DCOLOR_XRGB(255, 255, 255), this->isFlip);
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
		this->currentAnimation = this->animations->at(0);
		break;
	case WALKING:
		if (this->getState() != WALKING) {
			this->currentAnimation = this->animations->at(1);
		}
		break;
	case DROPPING:
		this->currentAnimation = this->animations->at(2);
		break;
	default:
		break;
	}

	this->state = _state;
}

//void Mario::updateCurrentAnimationByState()
//{
//	switch (this->getState())
//	{
//	case STANDING:
//		currentAnimation = this->animations->at(0);
//		break;
//	case WALKING:
//		if (this->getState() != WALKING) {
//			currentAnimation = this->animations->at(1);
//		}
//		break;
//	case DROPPING:
//		currentAnimation = this->animations->at(2);
//		break;
//	default:
//		break;
//	}
//}

void Mario::updateVelocity()
{
	switch (this->state)
	{
	case STANDING:
		this->plusCurrentVy(0);
		break;
	case WALKING:
		if (isFlip == false) { // Right sight
			if (abs(this->getVx()) + this->gravity <= this->maxVx) {
				this->plusCurrentVx(this->gravity);
			}
		}
		else { // Left sight
			if (abs(this->getVx()) - this->gravity <= this->maxVx) {
				this->plusCurrentVx(-this->gravity);
			}
		}
		break;
	case DROPPING:
		if (abs(this->getVy()) + this->gravity <= this->maxVy) {
			this->plusCurrentVy(this->gravity);
		}
		break;
	default:
		break;
	}
}

void Mario::onKeyUp()
{
	switch (this->state)
	{
	case STANDING:
		this->setVy(0);
		break;
	case DROPPING:
		this->setVx(0);
		break;
	default:
		break;
	}
}

void Mario::onKeyUp(KeyType _keyType)
{
	switch (_keyType)
	{
	case KeyType::left:
	case KeyType::right:
		this->setVx(0);
		if (this->getState() == WALKING) {
			this->setState(MarioState::STANDING);
		}
		break;
	default:
		break;
	}
}

void Mario::onKeyDown(KeyType _keyType)
{
	switch (_keyType)
	{
	case space:
		break;
	case up:
		break;
	case down:
		break;
	case KeyType::left:
		break;
	case KeyType::right:
		this->setIsFlip(false);
		if (this->getState() == STANDING) {
			this->setState(MarioState::WALKING);
		}
		break;
	default:
		break;
	}
}
