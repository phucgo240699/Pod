#include "MusicBox.h"

MusicBox::MusicBox(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

bool MusicBox::getIsSpecial()
{
	return this->isSpecial;
}

float MusicBox::getOriginX()
{
	return this->originX;
}

float MusicBox::getOriginY()
{
	return this->originY;
}

bool MusicBox::getIsTransparentMode()
{
	return this->isTransparentMode;
}

MusicBoxState MusicBox::getState()
{
	return this->state;
}

float MusicBox::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float MusicBox::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float MusicBox::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

float MusicBox::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

void MusicBox::setOriginX(float _originX)
{
	this->originX = _originX;
}

void MusicBox::setOriginY(float _originY)
{
	this->originY = _originY;
}

void MusicBox::setIsTransparentMode(bool _value)
{
	this->isTransparentMode = _value;
}

void MusicBox::setIsSpecial(bool _value)
{
	this->isSpecial = _value;
}

void MusicBox::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void MusicBox::setState(MusicBoxState _state)
{
	switch (_state)
	{
	case MUSIC_BOX_STAYING:
		break;
	case MUSIC_BOX_JUMPING_UP:
		this->isJumpingUp = true;
		break;
	case MUSIC_BOX_JUMPING_DOWN:
		this->isJumpingDown = true;
		break;
	case MUSIC_BOX_JUMPING_LEFT:
		this->isJumpingLeft = true;
		break;
	case MUSIC_BOX_JUMPING_RIGHT:
		this->isJumpingRight = true;
		break;
	default:
		break;
	}
	this->state = _state;
}

void MusicBox::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setIsSpecial(v[2] == 1);
	this->setIsTransparentMode(this->getIsSpecial());
	this->setId(v[3]);
	this->setOriginX(this->getX());
	this->setOriginY(this->getY());
}

void MusicBox::Update(float _dt)
{
	Component::Update(_dt);
	this->animation->Update(_dt);
	if (this->getState() == MUSIC_BOX_JUMPING_UP) {
		if (this->isJumpingUp) {
			if (this->getY() - jumpSpeed <= this->getOriginY() - this->jumpSpace) {
				this->setY(this->getOriginY() - this->jumpSpace);
				this->isJumpingUp = false;
			}
			else {
				this->plusY(-jumpSpeed);
			}
		}
		else {
			if (this->getY() + jumpSpeed >= this->getOriginY()) {
				this->setY(this->getOriginY());
				this->setState(MusicBoxState::MUSIC_BOX_STAYING);
			}
			else {
				this->plusY(jumpSpeed);
			}
		}
	}
	else if (this->getState() == MUSIC_BOX_JUMPING_DOWN) {
		if (this->isJumpingDown) {
			if (this->getY() + jumpSpeed >= this->getOriginY() + this->jumpSpace) {
				this->setY(this->getOriginY() + this->jumpSpace);
				this->isJumpingDown = false;
			}
			else {
				this->plusY(jumpSpeed);
			}
		}
		else {
			if (this->getY() - jumpSpeed <= this->getOriginY()) {
				this->setY(this->getOriginY());
				this->setState(MusicBoxState::MUSIC_BOX_STAYING);
			}
			else {
				this->plusY(-jumpSpeed);
			}
		}
	}
	else if (this->getState() == MUSIC_BOX_JUMPING_LEFT) {
		if (this->isJumpingLeft) {
			if (this->getX() - jumpSpeed <= this->getOriginX() - this->jumpSpace) {
				this->setX(this->getOriginX() - this->jumpSpace);
				this->isJumpingLeft = false;
			}
			else {
				this->plusX(-jumpSpeed);
			}
		}
		else {
			if (this->getX() + jumpSpeed >= this->getOriginX()) {
				this->setX(this->getOriginX());
				this->setState(MusicBoxState::MUSIC_BOX_STAYING);
			}
			else {
				this->plusX(jumpSpeed);
			}
		}
	}
	else if (this->getState() == MUSIC_BOX_JUMPING_RIGHT) {
		if (this->isJumpingRight) {
			if (this->getX() + jumpSpeed >= this->getOriginX() + this->jumpSpace) {
				this->setX(this->getOriginX() + this->jumpSpace);
				this->isJumpingRight = false;
			}
			else {
				this->plusX(jumpSpeed);
			}
		}
		else {
			if (this->getX() - jumpSpeed <= this->getOriginX()) {
				this->setX(this->getOriginX());
				this->setState(MusicBoxState::MUSIC_BOX_STAYING);
			}
			else {
				this->plusX(-jumpSpeed);
			}
		}
	}
}

void MusicBox::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getIsTransparentMode()) {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), D3DCOLOR_ARGB(0,255,255,255));
	}
	else {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
	}
}
