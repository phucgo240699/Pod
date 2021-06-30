#pragma once
#ifndef SUPERMUSHROOM_H
#define SUPERMUSHROOM_H

#include "Component.h"
#include "SuperMushroomState.h"
#include "AnimationBundle.h"
#include "Grid.h"
#include "Block.h"
#include "Camera.h"

class Mario;

class SuperMushroom : public Component
{
private:
	Animation* animation;
	SuperMushroomState state;
	bool moveLeftFirst;
	int endGrowupPoint;

	// Collision
	bool isStandOnSurface = false;
	int componentIdStanded;
public:
	// Init
	SuperMushroom(float _x, float _y, float _width, float _height, float _vx, float _vy, int _id, int _endGrowupPoint);

	// Getter
	SuperMushroomState getState();
	bool getIsStandOnSurface();

	// Setter
	void setAnimation(Animation* _animation);
	void setState(SuperMushroomState _state);
	void setIsStandOnSurface(bool _isStandOnSurface);

	void loadInfo(int _x, int _y, int _width, int _height, int _vx, int _vy, int _id);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	// Collision
	void handleHardComponentCollision(Component* _component, float _dt);
	void handleBlockCollision(Block* _block, float _dt);
	bool isCollideMario(Mario* _mario, float _dt);
};
#endif // !SUPERMUSHROOM_H