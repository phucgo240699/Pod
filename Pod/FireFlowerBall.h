#pragma once
#include "Component.h"
#include "FireFlowerBallState.h"
#include "AnimationBundle.h"

class Mario;

class FireFlowerBall : public Component
{
private:
	Animation* animation;
	FireFlowerBallState state;
	float originVx, originVy;
	float originX, originY;

public:
	// Init
	FireFlowerBall(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);


	// Getter
	FireFlowerBallState getState();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();
	

	// Setter
	void setState(FireFlowerBallState _state);
	void resetToOriginalPosition();

	//void loadInfo(string line, char seperator);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);


	// Collision
	void handleMarioCollision(Mario* _mario, float _dt);
};

