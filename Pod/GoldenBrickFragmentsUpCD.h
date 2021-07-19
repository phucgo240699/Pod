#pragma once
#include "AnimationCD.h"

class Camera;

class GoldenBrickFragmentsUpCD : public AnimationCD
{
private:
	float xLeft, xRight, originXLeft, originXRight;
	float y1, y2, y3, y4, originYTop, originYBottom;
	float limitY;
	// 1	2
	// 3	4
	Animation* brickFragment1, * brickFragment2, * brickFragment3, * brickFragment4;
public:
	GoldenBrickFragmentsUpCD(int _originXLeft, int _originXRight, int _originYTop, int _originYBottom);
	//~GoldenBrickFragmentsUpCD();

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};