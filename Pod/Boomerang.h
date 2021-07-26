#pragma once
#include "Component.h"
#include "AnimationBundle.h"
#include "BoomerangState.h"

class Mario;
class BoomerangBro;

class Boomerang : public Component
{
private:
	Animation* animation;
	BoomerangState state;
	float originVx, originVy;
	float countFlyingX, startFlyingY;

public:
	Boomerang(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	// Getter
	BoomerangState getState();
	int getHeight();
	int getWidth();
	int getBoundsHeight();
	int getBoundsWidth();
	Animation* getAnimation();


	// Setter
	void setState(BoomerangState _state);
	void setAnimation(Animation* _animation);


	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	void hanldeBoomerangBroCollision(BoomerangBro* _boomerangBro, float _dt);
	void handleMarioCollision(Mario* _mario, float _dt);
};
