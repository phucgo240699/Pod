#pragma once
#include "Component.h"
class GreenPipe : public Component
{
private:
	Animation* animation;
	int floorNumber;
public:
	// Init
	GreenPipe(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	GreenPipe(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	void setupAnimation();

	void loadInfo(string line, char seperator);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

