#include "PointCD.h"

PointCD::PointCD(Animation* _animation, int _pointX, int _pointY, int _endPointJumpUp) : AnimationCD(_animation)
{
	AnimationCD::AnimationCD(_animation);
	this->pointX = _pointX;
	this->pointY = _pointY;
	this->endPointJumpUp = _endPointJumpUp;
}

void PointCD::Update(float _dt)
{
	if (this->pointY - (2 * _dt) >= this->endPointJumpUp) {
		this->pointY -= (2 * _dt);
	}
	else {
		this->pointY = this->endPointJumpUp;
		this->setIsFinish(true);
	}
}

void PointCD::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), D3DXVECTOR3(this->pointX, this->pointY, 0));
}
