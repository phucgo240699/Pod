#pragma once
#include "AnimationCD.h"

class FlashLightCD : public AnimationCD
{
public:
	// Init
	FlashLightCD(Animation _animation, int _x, int _y);
	FlashLightCD(int _x, int _y);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};