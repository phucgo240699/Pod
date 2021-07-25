#pragma once
#include "Enemy.h"
#include "AnimationBundle.h"
#include "BossState.h"

class Boss : public Enemy
{
private:
	Animation* animation;
	BossState state;

	bool isFlyingMode = true;

	float movingWay = 50;
	//float flyingUpWay = 40;
	float countDownFromMovingToFlyingUp = movingWay;
	//float countDownFromFlyingUpToFlying = flyingUpWay;
	float countFlyingX, startFlyingY, countFlying = 0;
	float marioX;

public:
	// Init
	Boss(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);


	// Getter
	bool getIsStandOnSurface();
	BossState getState();
	RECT getFrame();
	bool getIsFlyingMode();
	float getMarioX();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();

	// Setter
	void setState(BossState _state);
	void setIsFlyingMode(bool _isFlyingMode);
	void setMarioX(float _marioX);

	void loadInfo(string line, char separator);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
	
	void handleHardComponentCollision(Component* _component, float _dt);
};
