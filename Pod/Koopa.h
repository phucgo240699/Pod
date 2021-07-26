#pragma once
#ifndef KOOPA_H
#define KOOPA_H

#include "Enemy.h"
#include "KoopaState.h"
#include "Camera.h"
#include "Grid.h"
#include "AnimationCDPlayer.h"
#include "GiftBrick.h"


class Mario; // Say Goomba exists without defining it.
class Goomba;
class FireBall;
class GoldenBrick;
class MusicBox;
class BoomerangBro;
class Boss;

class Koopa : public Enemy
{
private:
	Animation* animation;// , pointAnimation = Animation(0, 0, 0);
	KoopaState state;

	bool firstCheckAnim = true;
	int oldFrameHeight, oldFrameWidth;
	int newFrameHeight, newFrameWidth;

	float leftAnchor, rightAnchor;
	//float endPointJumpUp, pointX, pointY = -std::numeric_limits<float>::infinity();

	int countDown = 30, originCountDown = 30; // countDown to switch from standing to shaking, and from shaking to moving

	bool isFlip = false, isGreenMode = false, isFlyingMode = false;

	// Thrown away
	float thrownX, startThrownY;
	bool isOutOfFirstStage = true; // Just for red mode

	// Flying
	float countFlyingX, startFlyingY;

	// When mario turning around
	bool isShrinkageReverseMode = false;
	float countThrownToShrinkageX, startThrownToShrinkageY;


public:
	// Init
	Koopa(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	Koopa(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	void loadInfo(string line, char seperator);

	// Getter
	RECT getFrame();
	KoopaState getState();
	int getWidth();
	int getHeight();
	int getBoundsWidth();
	int getBoundsHeight();
	bool getIsFlip();
	bool getIsStandOnSurface();
	bool getHasCollideMario();
	bool getIsGreenMode();
	bool getIsFlyingMode();
	float getOriginVy();
	float getOriginVx();
	bool getIsShrinkageReverseMode();
	bool getIsOutOfFirstStage();

	// Setter
	void setState(KoopaState _state);
	void setIsFlip(bool _isFlip);
	void setupPointAnimPosition();
	void setHasCollideMario(bool _hasCollideMario);
	void setIsGreenMode(bool _isGreenMode);
	void setIsFlyingMode(bool _isFlyingMode);
	void setIsShrinkageReverseMode(bool _value);

	void convertMovingState();
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	// Collision
	void handleHardComponentCollision(Component* _component, float _dt);
	void handleGiftBrickCollision(GiftBrick* _giftBrick, Mario* _mario, float _dt);
	void handleBlockCollision(Component* _block, float _dt);
	void handleGoombaCollision(Goomba* _goomba, float _dt);
	void handleMarioCollision(Mario* _mario, float _dt);
	void handleFireBallCollision(FireBall* _fireBall, float _dt);
	void handleGoldenBrickCollision(GoldenBrick* _goldenBrick, float _dt);
	void handleKoopaCollision(Koopa* _koopa, float _dt);
	void handleMusicBoxCollision(MusicBox* _musicBox, float _dt);
	void handleBoomerangBroCollision(BoomerangBro* _boomerangBro, float _dt);
	void handleBossCollision(Boss* _boss, float _dt);
};

#endif // !KOOPA