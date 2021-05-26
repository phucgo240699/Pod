#pragma once
#include "Component.h"
class MainCharacter : public Component
{
private:
	float accelerationX = 0, accelerationY = 0;
	float targetVx = 0, targetVy = 0;
public:

	// Init
	MainCharacter(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	MainCharacter(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY);

	// De Init
	~MainCharacter();

	virtual void setState(MarioState _state);
	virtual Animation* getCurrentAnimation();

	float getAccelerationX();
	float getAccelerationY();
	float getTargetVx();
	float getTargetVy();

	void setAccelerationX(float _accelerationX);
	void setAccelerationY(float _accelerationY);
	void setTargetVx(float _targetVx);
	void setTargetVy(float _targetVy);
};