#pragma once
#include "Enemy.h"
#include "FireFlowerState.h"
#include "AnimationBundle.h"
#include "FireFlowerBall.h"
#include "Grid.h"

class Mario;
class Camera;
class FireBall;

class FireFlower : public Enemy
{
private:
	Animation* animation;
	FireFlowerState state;
	float originVy;
	float topAnchor, bottomAnchor, leftAnchor, rightAnchor;
	int countDown = 120;
	bool isFlip = false, isHalfSizeMode = false, isGreenMode = false;

	FireFlowerBall* fireFlowerBall;

	// Thrown away
	float thrownX, startThrownY;

public:
	// Init
	FireFlower(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);


	// Getter
	FireFlowerState getState();
	int getCountDown();
	bool getIsFlip();
	bool getIsGreenMode();
	bool getIsHalfSizeMode();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();
	float getTopAnchor();
	float getBottomAnchor();
	float getLeftAnchor();
	float getRightAnchor();
	//FireFlowerBall* getFireFlowerBall();

	// Setter
	void setFireFlowerBallAnimation(Animation* _animation);
	void setState(FireFlowerState _state);
	void setFireFlowerBallState(FireFlowerBallState _fireFlowerBallState);
	void setIsFlip(bool _isFlip);
	void setIsGreenMode(bool _isGreenMode);
	void setIsHalfSizeMode(bool _isHalfSizeMode);
	void reduceCountDown();

	void loadInfo(string line, char seperator);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);


	// Collision
	void handleMarioCollision(Mario* _mario, float _dt);
	void handleFireBallCollision(FireBall* _fireBall, float _dt);
};