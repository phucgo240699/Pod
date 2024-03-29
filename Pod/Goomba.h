#pragma once
#ifndef GOOMBA_H
#define GOOMBA_H

#include "Enemy.h"
#include "GoombaState.h"
#include "AnimationBundle.h"
#include "Camera.h"
#include "Grid.h"
#include "AnimationCDPlayer.h"

class Mario; // Say Goomba exists without defining it.
class Koopa;
class FireBall;

class Goomba : public Enemy
{
private:
	Animation* animation;
	GoombaState state;

	bool alreadyPlayPointCD = false;
	int countDownToDead = 12;
	float thrownX, startThrownY;

	// Flying
	bool isFlyingMode = false, isUseRedSkin = false;
	float countFlyingX, startFlyingY, countPoppingX, startPoppingY, countPopping, countDownFromMovingToFlying = 40;
	//float storedVy;
	float marioX;

public:
	// Init
	Goomba(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	Goomba(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	void loadInfo(string line, char seperator);

	// Getter
	GoombaState getState();
	bool getIsStandOnSurface();
	bool getIsFlyingMode();
	float getMarioX();
	int getWidth();
	int getHeight();
	int getBoundsWidth();
	int getBoundsHeight();
	//float getStoredVy();
	float getOriginVx();
	float getOriginVy();
	RECT getFrame();

	// Setter
	void setState(GoombaState _state);
	void setIsFlyingMode(bool _isFlyingMode);
	void setMarioX(float _marioX);
	//void setStoredVy(float _storedVy);


	void convertMovingState();
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	// Collision
	void handleHardComponentCollision(Component* _component, float _dt);
	void handleBlockCollision(Component* _block, float _dt);
	void handleKoopaCollision(Koopa* _koopa, float _dt);
	void handleMarioCollision(Mario* _mario, float _dt);
	void handleFireBallCollision(FireBall* _fireBall, float _dt);
};

#endif // !GOOMBA_H