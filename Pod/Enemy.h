#pragma once
#include "Component.h"

class Enemy : public Component
{
protected:

public:
	// Init
	Enemy(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	Enemy(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

};