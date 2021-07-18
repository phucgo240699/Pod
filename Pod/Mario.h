#pragma once
#ifndef MARIO_H
#define MARIO_H

#include "MarioState.h"
#include "KeyType.h"
#include "Camera.h"
#include "Animation.h"
#include "MainCharacter.h"
#include "Ground.h"
#include "GoldenBrick.h"
#include "GiftBrick.h"
#include "ScoreBoard.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Block.h"
#include "GreenPipe.h"
#include "SuperLeaf.h"
#include "FireFlower.h"
#include "Flower.h"
#include "FireBall.h"
#include <unordered_map>

using namespace std;

class Mario : public MainCharacter
{
private:
	LPDIRECT3DTEXTURE9 texture;
	MarioState state;
	MarioSubState subState;
	MarioState pressureState; // Hold state of mario before scaling up or scaling down
	Animation* currentAnimation;
	Animation* pressureAnimation;
	FireBall* firstFireBall;

	// Control
	bool isStandOnSurface = false, isReduceWalking = false, isConverting = false, isTurningAround = false, isPressA = false;
	bool isFlip; // false: Left side - true: Right side. Default is false

	// Mode
	bool isSuperMode = false, isFlashMode = false, debugMode = true, isFireMode = false, isCloudMode = false, isFlyingMode = false;

	// Validate Animation
	int oldFrameHeight, oldFrameWidth;
	int newFrameHeight, newFrameWidth;

	// Point
	int pointCoef = 0;
	int countDownFlash = 120;

	// Bounds vs Frame
	int leftSpace, topSpace, rightSpace;
	int marioLeftSpace, marioTopSpace, marioRightSpace;
	int superMarioLeftSpace, superMarioTopSpace, superMarioRightSpace;
	int superMarioFlyingLeftSpace, superMarioFlyingTopSpace, superMarioFlyingRightSpace;

	// Momentum to fly
	int momentumToFly = 0;

public:
	// Init
	Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);
	Mario(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);
	
	//
	// =============== Getter ===============
	//
	MarioState getState();
	MarioSubState getSubState();
	MarioState getPressureState(); // Hold state of mario before scaling up or scaling down
	Animation* getCurrentAnimation();
	Animation* getPressureAnimation();
	FireBall* getFirstFireBall();
	RECT getBounds();

	float getBoundsWidth();
	float getBoundsHeight();
	float getWidth();
	float getHeight();

	// Control
	bool getIsFlip();
	bool getIsConverting();
	bool getIsReduceWalking();
	bool getIsStandOnSurface();
	bool getIsTurningAround();
	bool getIsPressA();
	
	// Mode
	bool getIsSuperMode();
	bool getIsFlashMode();
	bool getIsFireMode();
	bool getIsCloudMode();
	bool getIsFlyingMode();


	// Point
	int getPointCoef();

	// Bounds vs Frame
	int getLeftSpace();
	int getTopSpace();
	int getRightSpace();
	int getMarioLeftSpace();
	int getMarioTopSpace();
	int getMarioRightSpace();
	int getSuperMarioLeftSpace();
	int getSuperMarioTopSpace();
	int getSuperMarioRightSpace();
	int getSuperMarioFlyingLeftSpace();
	int getSuperMarioFlyingTopSpace();
	int getSuperMarioFlyingRightSpace();


	// Momentum to fly
	int getMomentumToFly();


	//
	// =============== Setter ===============
	//
	void setFirstFireBallAnimation(Animation* _animation);
	void setState(MarioState _state);
	void setSubState(MarioSubState _subState);
	void setPressureState(MarioState _pressureState);
	void setPressureAnimation(Animation _animation);

	// Control
	void setIsFlip(bool _isFlip);
	void setIsConverting(bool _isConverting);
	void setIsReduceWalking(bool _isReduceWalking);
	void setIsStandOnSurface(bool _isStandOnSurface);
	void setupReduceWalking(bool _isReduceWalking);
	void setIsTurningAround(bool _isTurningAround);
	void setIsPressA(bool _isPressA);
	
	// Mode
	void setIsSuperMode(bool _isSuperMode);
	void setIsFlashMode(bool _isFlashMode);
	void turnOnFireSkin(MarioState _state);
	void turnOffFireSkin(MarioState _state);
	void setIsFireMode(bool _isFireMode);
	void setIsCloudMode(bool _isCloudMode);
	void setIsFlyingMode(bool _isFlyingMode);
	void toggleFlyingMode();
	void turnOnTurningAroundSkin();
	void turnOffTurningAroundSkin();


	// Point
	void increasePointCoef(); // this method will add pointCoeft to 1.
	void resetPointCoef(); // this method will set pointCoef to 0.

	// Bounds vs Frame
	void setLeftSpace(int _space);
	void setTopSpace(int _space);
	void setRightSpace(int _space);
	void setMarioLeftSpace(int _space);
	void setMarioTopSpace(int _space);
	void setMarioRightSpace(int _space);
	void setSuperMarioLeftSpace(int _space);
	void setSuperMarioTopSpace(int _space);
	void setSuperMarioRightSpace(int _space);
	void setSuperMarioFlyingLeftSpace(int _space);
	void setSuperMarioFlyingTopSpace(int _space);
	void setSuperMarioFlyingRightSpace(int _space);
	void setFirstFireBallState(FireBallState _state);


	// Update & Draw
	void updateVelocity();
	void Update(float _dt);
	void Draw();

	// Keyboard
	void onKeyUp();
	void onKeyUp(vector<KeyType> _keyTypes);
	void onKeyDown(vector<KeyType> _keyTypes);


	void loadInfo(string line, char seperator);


	// Collision
	void handleGroundCollision(Ground* _ground, float _dt);
	void handleBlockCollision(Block* _block, float _dt);
	void handleGoldenBrickCollision(GoldenBrick* _goldenBrick, float _dt);
	void handleGiftBrickCollision(GiftBrick* _giftBrick, float _dt);
	void handleGreenPipeCollision(GreenPipe* _greenPipe, float _dt);
	void handleGoombaCollision(Goomba* _goomba, float _dt);
	void handleKoopaCollision(Koopa* _koopa, float _dt);
	void handleSuperMushroomCollision(SuperMushroom* _superMushroom, float _dt);
	void handleSuperLeafCollision(SuperLeaf* _superLeaf, float _dt);
	void handleFireFlowerCollision(FireFlower* _fireFlower, float _dt);
	void handleFireFlowerBallCollision(FireFlowerBall* _fireFlowerBall, float _dt);
	void handleFlowerCollision(Flower* _flower, float _dt);
};

#endif // !MARIO_H