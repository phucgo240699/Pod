#pragma once
#include "Component.h"

class Enemy : public Component
{
protected:

	float originVx, originVy;

	int pointCoef;
	int defaultPoint;

	// Collision
	bool isStandOnSurface = false, isFlip = false, hasCollideMario = false;

public:
	// Init
	Enemy(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	Enemy(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	// Getter
	int getPointCoef();
	int getDefaultPoint();

	// Setter
	void setIsStandOnSurface(bool _isStandOnSurface);
	void setPointCoef(int _pointCoef);

	void Update(float _dt);
};