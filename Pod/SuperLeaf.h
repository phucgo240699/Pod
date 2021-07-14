#pragma once
#ifndef SUPERLEAF_H
#define SUPERLEAF_H

#include "Component.h"
#include "SuperLeafState.h"
#include "AnimationBundle.h"

class Mario;

class SuperLeaf : public Component
{
private:
	Animation* animation;
	SuperLeafState state;

	float originVx, originVy;

	// Popping
	float limitPoppingUp;

	// Dropping
	bool isFlip = false;
	float leftX, rightX, topY;

public:
	// Init
	SuperLeaf(float _x, float _y, float _width, float _height, float _vx, float _vy, int _id);

	// Getter
	bool getIsFlip();
	SuperLeafState getState();

	// Setter
	void setIsFlip(bool _isFlip);
	void setAnimation(Animation* _animation);
	void setState(SuperLeafState _state);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	// Collision
	void handleMarioCollision(Mario* _mario, float _dt);
};

#endif // !SUPERLEAF_H