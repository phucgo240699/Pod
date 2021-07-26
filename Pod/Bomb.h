#pragma once
#include "Component.h"
#include "BombState.h"

class Mario;

class Bomb : public Component
{
private:
	Animation* animation;
	BombState state;

	float originVx, originVy;
	float countDroppingY, startDroppingX;

public:
	// Init
	Bomb(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	// Getter
	BombState getState();

	int getWidth();
	int getHeight();
	int getBoundsWidth();
	int getBoundsHeight();

	// Setter
	void setState(BombState _state);
	void setAnimation(Animation* _animation);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	void handleMarioCollision(Mario* _mario, float _dt);
};
