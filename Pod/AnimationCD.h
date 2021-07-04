#pragma once
#include "Animation.h"

class AnimationCD
{
private:
	Animation* animation;
	float beginX = 0, endX = 0;
	float beginY = 0, endY = 0;
	float x = 0, vx = 0;
	float y = 0, vy = 0;

public:
	AnimationCD(float _beginX, float _endX, float _beginY, float _endY, Animation* _animation);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

