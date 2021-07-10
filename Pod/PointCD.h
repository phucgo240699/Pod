#pragma once
#include "AnimationCD.h"

class PointCD : public AnimationCD
{
private:
	int pointX, pointY, endPointJumpUp;

public:
	// Init
	PointCD(Animation* _animation, int _pointX, int _pointY, int _endPointJumpUp);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

