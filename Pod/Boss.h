#pragma once
#include "Enemy.h"
#include "AnimationCDPlayer.h"
#include "BossState.h"
#include "Bomb.h"

class Mario;
class FireBall;
class Koopa;


class Boss : public Enemy
{
private:
	Animation* animation;
	BossState state;
	Bomb* firstBomb, * secondBomb, * thirdBomb;

	bool isFlyingMode = true;

	float movingWay = 50;

	float countDownFromMovingToFlyingUp = movingWay;

	float countFlyingX, startFlyingY, countFlying = 0;
	float marioX;
	int countDownToDead = 12;

	float countThrowingX, startThrowingY;

public:
	// Init
	Boss(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);


	// Getter
	bool getIsStandOnSurface();
	BossState getState();
	RECT getFrame();
	bool getIsFlyingMode();
	float getMarioX();
	int getWidth();
	int getHeight();
	int getBoundsWidth();
	int getBoundsHeight();

	Bomb* getFirstBomb();
	Bomb* getSecondBomb();
	Bomb* getThirdBomb();

	// Setter
	void setState(BossState _state);
	void setIsFlyingMode(bool _isFlyingMode);
	void setMarioX(float _marioX);

	void loadInfo(string line, char separator);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
	
	void handleHardComponentCollision(Component* _component, float _dt);
	void handleBlockComponentCollision(Component* _component, float _dt);
	void handleMarioCollision(Mario* _mario, float _dt);
	void handleFireBallCollision(FireBall* _fireBall, float _dt);
	void handleKoopaCollision(Koopa* _koopa, float _dt);
};
