#pragma once
#include "Component.h"

class Block : public Component
{

public:
	Block(float _x, float _y, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY);
	Block(D3DXVECTOR3 _position, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY);

	void load(string line, char seperator);
};

