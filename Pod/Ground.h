#pragma once

#include "Component.h";

class Ground : public Component
{

public:
	Ground(float _x, float _y, int _width, int _height, float _vx, float _vy, float _limitX, float _limitY);
	Ground(D3DXVECTOR3 _position, int _width, int _height, float _vx, float _vy, float _limitX, float _limitY);

	void load(string line, char seperator);
};

