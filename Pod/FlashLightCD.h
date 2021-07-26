#pragma once
#include "AnimationCD.h"

class FlashLightCD : public AnimationCD
{
public:
	// Init
	FlashLightCD(Animation _animation, float _x, float _y);
	FlashLightCD(float _x, float _y);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};