#pragma once
#include "AnimationCD.h"

class PointUpCD : public AnimationCD
{
private:
	int endY;

public:
	// Init
	//PointUpCD(Animation _animation, int _x, int _y, int _endY);
	PointUpCD(Animation _animation, int _x, int _y);
	//PointUpCD(int point, int _x, int _y, int _endY);
	PointUpCD(int point, int _x, int _y);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

