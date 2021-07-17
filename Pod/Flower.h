#pragma once
#include "Enemy.h"
#include "FlowerState.h"
#include "AnimationBundle.h"
#include "Grid.h"

class Mario;
class Camera;
class FireBall;

class Flower : public Enemy
{
private:
	Animation* animation;
	FlowerState state;
	float originVy;
	float topAnchor, bottomAnchor, leftAnchor, rightAnchor;
	int countDown = 120;
	bool isHalfSizeMode = false, isGreenMode = false;

public:
	// Init
	Flower(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);


	// Getter
	FlowerState getState();
	int getCountDown();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();
	float getTopAnchor();
	float getBottomAnchor();
	float getLeftAnchor();
	float getRightAnchor();
	bool getIsHalfSizeMode();
	bool getIsGreenMode();


	// Setter
	void setState(FlowerState _state);
	void reduceCountDown();
	void setIsHalfSizeMode(bool _isHalfSizeMode);
	void setIsGreenMode(bool _isGreenMode);


	void loadInfo(string line, char seperator);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);


	// Collision
	void handleMarioCollision(Mario* _mario, float _dt);
	void handleFireBallCollsion(FireBall* _fireBall, float _dt);
};