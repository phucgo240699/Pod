#pragma once
#include "Component.h"

class WTurtle : public Component
{
private:
	bool isFlip = false;
	float leftAnchor = 0, rightAnchor = 0;

	Animation* animation;
	long startTime = GetTickCount();
public:
	// Init
	WTurtle(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	WTurtle(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY);

	// Getter
	float getWidth();
	float getHeight();

	void loadInfo(string line, char seperator);
	void loadAnimation(Animation* _animation);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

};

