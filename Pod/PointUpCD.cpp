#include "PointUpCD.h"

//PointUpCD::PointUpCD(Animation _animation, int _x, int _y, int _endY) : AnimationCD(_animation)
//{
//	AnimationCD::AnimationCD(_animation);
//	this->x = _x;
//	this->y = _y;
//	this->endY = _endY;
//}

PointUpCD::PointUpCD(Animation _animation, int _x, int _y) : AnimationCD(_animation)
{
	AnimationCD::AnimationCD(_animation);
	this->position.x = _x;
	this->position.y = _y;
	this->endY = _y - 48;
}

//PointUpCD::PointUpCD(int point, int _x, int _y, int _endY) : AnimationCD(Animation(AnimationBundle::getInstance()->getPoints(point)))
//{
//	AnimationCD::AnimationCD(Animation(AnimationBundle::getInstance()->getPoints(point)));
//	this->x = _x;
//	this->y = _y;
//	this->endY = _endY;
//}

PointUpCD::PointUpCD(int point, int _x, int _y) : AnimationCD(Animation(AnimationBundle::getInstance()->getPoints(point)))
{
	AnimationCD::AnimationCD(Animation(AnimationBundle::getInstance()->getPoints(point)));
	this->position.x = _x;
	this->position.y = _y;
	this->endY = _y - 48;
}

void PointUpCD::Update(float _dt)
{
	if (this->position.y - (2 * _dt) >= this->endY) {
		this->position.y -= (2 * _dt);
	}
	else {
		this->position.y = this->endY;
		this->setIsFinish(true);
	}
}

void PointUpCD::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation.getCurrentFrame(), this->position);
}
