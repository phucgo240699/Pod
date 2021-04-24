#include "Mario.h"

Mario::Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state = STANDING) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_imagePath, &info);
	this->width = info.Width;
	this->height = info.Height;

	this->state = _state;
}

Mario::Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state = STANDING) : Component(_position, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_position, _vx, _vy, _limitX, _limitY);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_imagePath, &info);
	this->width = info.Width;
	this->height = info.Height;

	this->state = _state;
}

Mario::~Mario()
{
	Component::~Component();
	delete& texture;
}

MarioState Mario::getState()
{
	return this->state;
}

RECT* Mario::getBounds()
{
	RECT* r = new RECT();

	r->top = this->getY();
	r->bottom = this->getY() + this->height;
	r->left = this->getX();
	r->right = this->getX() + this->width;

	return r;
}

void Mario::setState(MarioState _state)
{
	this->state = _state;
}

void Mario::Update(float _dt)
{
	if (0 <= this->getX() + this->width + this->vx && this->getX() + this->width + this->vx < this->limitX) {
		this->plusX(this->vx * _dt);
	}
	if (0 <= this->getY() + this->height + this->vy && this->getY() + this->height + this->vy < this->limitY) {
		this->plusY(this->vy * _dt);
	}
}

void Mario::Draw()
{
	Camera* camera = Camera::getInstance();
	D3DXVECTOR3* validPosition = new D3DXVECTOR3(*(this->position));
	if (camera->getOnTopSafeArea()) {

	}
	else if (camera->getOnBottomSafeArea()) {
		validPosition->y -= camera->getY();
	}
	if (camera->getOnLeftSafeArea()) {

	}
	else if (camera->getOnRightSafeArea()) {
		validPosition->x -= camera->getX();
	}
	
	if (!camera->getOnTopSafeArea() && !camera->getOnBottomSafeArea()){
		validPosition->y = camera->getHeight() / 2 - this->height / 2;
	}
	if (!camera->getOnLeftSafeArea() && !camera->getOnRightSafeArea()) {
		validPosition->x = camera->getWidth() / 2 - this->width / 2;
	}
	Drawing::getInstance()->draw(this->texture, NULL, NULL, validPosition, D3DCOLOR_XRGB(255,255,255));
}

void Mario::onKeyUp()
{
	this->vx = 0;
	this->vy = 0;
}

void Mario::onKeyDown(KeyType _keyType)
{
	switch (_keyType)
	{
	case KeyType::up:
		this->vy = -2;
		break;
	case KeyType::down:
		this->vy = 2;
		break;
	case KeyType::left:
		this->vx = -2;
		break;
	case KeyType::right:
		this->vx = 2;
		break;
	default:
		break;
	}
}
