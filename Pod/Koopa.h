#pragma once
#ifndef KOOPA_H
#define KOOPA_H

#include "Enemy.h"
#include "KoopaState.h"
#include "AnimationBundle.h"
#include "Camera.h"
#include "Grid.h"

class Mario; // Say Goomba exists without defining it.

class Koopa : public Enemy
{
private:
	Animation* animation, * pointAnimation;
	KoopaState state;
	float originVx, originVy;

	int leftAnchor, rightAnchor;
	int endPointJumpUp, pointX, pointY;
	int pointCoef;
	int defaultPoint;

	// Collision
	bool isStandOnSurface = false, isFlip = false;

public:
	// Init
	Koopa(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	Koopa(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	void loadInfo(string line, char seperator);

	// Getter
	KoopaState getState();
	float getWidth();
	float getHeight();
	bool getIsFlip();
	bool getIsStandOnSurface();
	int getPointCoef();
	int getDefaultPoint();

	// Setter
	void setState(KoopaState _state);
	void setIsFlip(bool _isFlip);
	void setIsStandOnSurface(bool _isStandOnSurface);
	void setPointCoef(int _pointCoef);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	// Collision
	void handleHardComponentCollision(Component* _component, float _dt);
	void handleBlockCollision(Component* _block, float _dt);
	void handleMarioCollision(Mario* _mario, float _dt);
};

#endif // !KOOPA