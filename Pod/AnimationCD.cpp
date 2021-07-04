#include "AnimationCD.h"

AnimationCD::AnimationCD(float _beginX, float _endX, float _beginY, float _endY, Animation* _animation)
{
	animation = _animation;
	beginX = _beginX;
	endX = _endX;
	beginY = _beginY;
	endY = _endY;
}

void AnimationCD::Update(float _dt)
{
	if (beginX != 0 || endX != 0) {
		if (vx > 0) {
			if (x + vx <= endX) {
				x += vx;
			}
			else {
				x = endX;
			}
		}
		else if (vx < 0) {

		}
	}
}

void AnimationCD::Draw(LPDIRECT3DTEXTURE9 _texture)
{
}
