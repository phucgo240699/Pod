#pragma once
#include "Component.h"
#include "Camera.h"

class GoldenBrick : public Component
{
private:
	Animation* animation;

public:
	GoldenBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	GoldenBrick(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	void loadInfo(string line, char seperator);
	void loadAnimation(vector<string> data, char endSeperator, char seperator);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

