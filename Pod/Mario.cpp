#include "Mario.h"

Mario::Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);

	/*D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_imagePath, &info);
	this->width = info.Width;
	this->height = info.Height;*/

	this->state = _state;

	// Animations
	//this->animations->push_back(new MarioStandingLeft(0, 0, 2, "Mario/standing_left.txt"));

	this->currentAnimation = new MarioStandingLeft(0, 0, 2, "Mario/standing_left.txt"); // this->animations->at(0);
}

Mario::Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state) : Component(_position, _vx, _vy, _limitX, _limitY)
{
	Component::Component(_position, _vx, _vy, _limitX, _limitY);
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);

	/*D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_imagePath, &info);
	this->width = info.Width;
	this->height = info.Height;*/

	this->state = _state;
}

Mario::~Mario()
{
	Component::~Component();
	delete& texture;
	delete& state;
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
}

void Mario::Update(float _dt)
{
	/*if (0 <= this->getX() + this->width + this->vx && this->getX() + this->width + this->vx < this->limitX) {
		this->plusX(this->vx * _dt);
	}
	if (0 <= this->getY() + this->height + this->vy && this->getY() + this->height + this->vy < this->limitY) {
		this->plusY(this->vy * _dt);
	}*/
	if (currentAnimation == NULL) {
		return;
	}
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
		validPosition->y = camera->getHeight() / 2 - marioHeight / 2;
	}
	if (!camera->getOnLeftSafeArea() && !camera->getOnRightSafeArea()) {
		validPosition->x = camera->getWidth() / 2 - marioWidth / 2;
	}
	//Drawing::getInstance()->draw(this->texture, NULL, NULL, validPosition, D3DCOLOR_XRGB(255,255,255));
	this->currentAnimation->Draw(this->texture, validPosition, D3DCOLOR_XRGB(255, 255, 255));
}

void Mario::onKeyUp()
{
	//this->vx = 0;
	//this->vy = 0;
}

void Mario::onKeyDown(KeyType _keyType)
{
	//switch (_keyType)
	//{
	//case KeyType::up:
	//	this->vy = -2;
	//	break;
	//case KeyType::down:
	//	this->vy = 2;
	//	break;
	//case KeyType::left:
	//	this->vx = -2;
	//	break;
	//case KeyType::right:
	//	this->vx = 2;
	//	break;
	//default:
	//	break;
	//}
}
