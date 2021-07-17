#pragma once
#include "Component.h"
#include "AnimationBundle.h"
#include "FireBallState.h"

class Mario;

class FireBall : public Component
{
private:
	Animation* animation;
	FireBallState state;
	float originVx;
	float originX, originY;
	bool isOutOfGrid = true;

public:
	// Init
	FireBall(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);


	// Getter
	FireBallState getState();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();
	bool getIsOutOfGrid();


	// Setter
	void setAnimation(Animation* _animation);
	void setState(FireBallState _state);
	void resetToOriginalPosition();
	void setIsOutOfGrid(bool _isOutOfGrid);

	//void loadInfo(string line, char seperator);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);


	// Collision
	void handleMarioCollision(Mario* _mario, float _dt);
};
