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
	Animation* animation , * pointAnimation;
	SuperMushroomState state;
	D3DXVECTOR3 pointPosition;// = D3DXVECTOR3(0, 0, 0);
	bool moveLeftFirst;
	int endGrowUpY, countDownToDisappear = 12;
	int endPointJumpUp;// , pointY;

	// Collision
	bool isStandOnSurface = false;

	int defaultPoints;

	// Mode
	bool isGreenMode = false;

public:
	// Init
	SuperMushroom(float _x, float _y, int _width, int _height, float _vx, float _vy, int _id);

	// Getter
	SuperMushroomState getState();
	bool getIsStandOnSurface();
	int getDefaultPoints();
	int getBoundsWidth();
	int getBoundsHeight();
	bool getIsGreenMode();


	// Setter
	void setUpAnimation();
	void setState(SuperMushroomState _state);
	void setIsStandOnSurface(bool _isStandOnSurface);
	void setDefaultPoints(int _defaultPoints);
	void setIsGreenMode(int _isGreenMode);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	// Collision
	void handleHardComponentCollision(Component* _component, float _dt);
	void handleBlockCollision(Block* _block, float _dt);
	void handleMarioCollision(Mario* _mario, float _dt);
};
#endif // !SUPERMUSHROOM_H