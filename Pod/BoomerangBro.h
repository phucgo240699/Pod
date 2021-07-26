#pragma once
#include "Enemy.h"
#include "BoomerangBroState.h"
#include "AnimationBundle.h"
#include "Boomerang.h"

class Mario;
class FireBall;
class Koopa;

class BoomerangBro : public Enemy
{
private:
	Animation* animation;
	BoomerangBroState state;
	Boomerang* firstBoomerang, * secondBoomerang;
	Animation* throwingAnim;

	float originVx, originVy;
	float countFlyingX, startFlyingY;
	bool isHolding = false;
	int totalMoving = 3, countMoving = 0;
	float leftAnchor, rightAnchor;
	bool isFlip = false;
	int countDownToThrowBoomerang = 1600;
	float marioX;
	int countDownFinishStartThrow = 8;

public:
	// Init
	BoomerangBro(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	void loadInfo(string line, char seperator);

	// Getter
	bool getIsStandOnSurface();
	BoomerangBroState getState();
	bool getIsHolding();
	bool getIsFlip();
	int getHeight();
	int getWidth();
	int getBoundsHeight();
	int getBoundsWidth();
	Boomerang* getFirstBoomerang();
	Boomerang* getSecondBoomerang();
	RECT getFrame();


	// Setter
	void setState(BoomerangBroState _state);
	void setIsHolding(bool _isHoldinng);
	void setIsFlip(bool _isFlip);
	void setMarioX(float _value);


	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	void hanldeHardComponentCollision(Component* _component, float _dt);
	void handleBoomerangCollision(Boomerang* _boomerang, float _dt);
	void handleMarioCollision(Mario* _mario, float _dt);
	void handleFireBallCollision(FireBall* _fireBall, float _dt);
	void handleKoopaCollision(Koopa* _koopa, float _dt);
};

