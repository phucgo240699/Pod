#pragma once
#ifndef SUPERLEAF_H
#define SUPERLEAF_H

#include "Component.h"
#include "SuperLeafState.h"
#include "AnimationBundle.h"


class SuperLeaf : public Component
{
private:
	Animation* animation;
	SuperLeafState state;

public:
	// Init
	SuperLeaf(float _x, float _y, float _width, float _height, float _vx, float _vy, int _id);

	// Getter
	SuperLeafState getState();

	// Setter
	void setAnimation(Animation* _animation);
	void setState(SuperLeafState _state);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

#endif // !SUPERLEAF_H