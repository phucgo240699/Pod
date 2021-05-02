#include "Mario.h"

void Mario::setUpAnimations()
{
	this->animations = new vector<Animation*>();

	this->animations->push_back(new Animation(0, 0, 2, "Mario/standing.txt"));

	this->currentAnimation = this->animations->at(0);
}

Mario::Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->state = _state;
	this->setState(_state);
	setUpAnimations();
}

Mario::Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : Component(_position, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_position, _vx, _vy, _limitX, _limitY);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->state = _state;
	this->setState(_state);
	setUpAnimations();
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

void Mario::setState(MarioState _state)
{
	this->state = _state;
	if (_state == MarioState::STANDING_RIGHT) {
		this->isFlip = true;
	}
	else {
		this->isFlip = false;
	}
}

void Mario::updateCurrentAnimation(MarioState _state)
{
	switch (_state)
	{
	case DROPPING:
		break;
	case STANDING_LEFT:
		if (_state != STANDING_RIGHT && _state != STANDING_LEFT) { // increase performance 2.
			currentAnimation = this->animations->at(0);
		}
		break;
	case STANDING_RIGHT:
		if (_state != STANDING_LEFT && _state != STANDING_RIGHT) {
			currentAnimation = this->animations->at(0);
		}
		break;
	case JUMPING:
		break;
	case WALKING_RIGHT:
		break;
	case WALKING_LEFT:
		break;
	default:
		break;
	}
}

void Mario::Update(float _dt)
{
	if (currentAnimation == NULL) {
		return;
	}

	this->updateCurrentAnimation(this->state);
	this->currentAnimation->Update(_dt);
}

void Mario::Draw()
{
	if (currentAnimation == NULL) {
		return;
	}
	Camera* camera = Camera::getInstance();
	D3DXVECTOR3* validPosition = new D3DXVECTOR3(*(this->position));
	float marioWidth = this->currentAnimation->getCurrentFrame()->right - this->currentAnimation->getCurrentFrame()->left;
	float marioHeight = this->currentAnimation->getCurrentFrame()->bottom - this->currentAnimation->getCurrentFrame()->top;
	
	if (camera->getOnBottomSafeArea()) {
		validPosition->y -= camera->getY();
	}
	if (camera->getOnRightSafeArea()) {
		validPosition->x -= camera->getX();
	}
	
	if (!camera->getOnTopSafeArea() && !camera->getOnBottomSafeArea()){
		validPosition->y = camera->getHeight() / 2 - marioHeight / 2;
	}
	if (!camera->getOnLeftSafeArea() && !camera->getOnRightSafeArea()) {
		validPosition->x = camera->getWidth() / 2 - marioWidth / 2;
	}
	
	this->currentAnimation->Draw(this->texture, validPosition, D3DCOLOR_XRGB(255, 255, 255), this->isFlip);
}

void Mario::onKeyUp()
{

}

void Mario::onKeyDown(KeyType _keyType)
{
	switch (_keyType)
	{
	case KeyType::right:
		if (this->state != STANDING_RIGHT) { // increase performance 1
			this->setState(MarioState::STANDING_RIGHT);
		}
		break;
	case KeyType::left:
		if (this->state != STANDING_LEFT) {
			this->setState(MarioState::STANDING_LEFT);
		}
		break;
	default:
		break;
	}
}
