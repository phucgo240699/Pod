#pragma once
#include "Component.h"
class MainCharacter : public Component
{
public:

	// Init
	MainCharacter(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	MainCharacter(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY);

	// De Init
	~MainCharacter();

	virtual void setState(MarioState _state);
	virtual Animation* getCurrentAnimation();
};