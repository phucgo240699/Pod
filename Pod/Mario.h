#pragma once
#ifndef MARIO_H
#define MARIO_H

#include "MarioState.h"
#include "KeyType.h"
#include "Camera.h"
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
#include "Coin.h"
#include "PButton.h"
#include "MusicBox.h"
#include "BoomerangBro.h"
#include "Boss.h"
#include "Bomb.h"
#include "Item.h"
#include <unordered_map>

using namespace std;

class Mario : public MainCharacter
{
private:
	//LPDIRECT3DTEXTURE9 texture;
	MarioState state;
	MarioSubState subState;
	MarioState pressureState; // Hold state of mario before scaling up or scaling down
	Animation* currentAnimation;
	Animation* pressureAnimation;
	FireBall* firstFireBall;
	
	Animation* firstBombAnim, * secondBombAnim, * thirdBombAnim;

	// Control
	bool isStandOnSurface = false, isReduceWalking = false, isConverting = false, isTurningAround = false, isPressA = false, isPressKeyUp = false, isPressKeyS = false;
	bool isFlip; // false: Left side - true: Right side. Default is false

	// Mode
	bool isSuperMode = false, isFlashMode = false, debugMode = true, isFireMode = false, isCloudMode = false, isFlyingMode = false, isPreFlyingUpMode = false, isFlyingUpMode = false;

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
	int momentumSpace = 12;
	int momentumLevelToFly = 0;

	// Tail
	int tailMarginTop, tailMarginBottom, tailWidth, tailHeight;

	// Bomb Attack
	int numberBombsAttached = 0;

	// Detect component standing on
	int componentIdStandingOn;
	int endDroppingDownPipe;
	int endPoppingUpPipe;

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
	RECT getFrame();

	int getBoundsWidth();
	int getBoundsHeight();
	int getWidth();
	int getHeight();

	// Control
	bool getIsFlip();
	bool getIsConverting();
	bool getIsReduceWalking();
	bool getIsStandOnSurface();
	bool getIsTurningAround();
	bool getIsPressA();
	bool getIsPressKeyUp();
	bool getIsPressKeyS();
	
	// Mode
	bool getIsSuperMode();
	bool getIsFlashMode();
	bool getIsFireMode();
	bool getIsCloudMode();
	bool getIsFlyingMode();
	bool getIsPreFlyingUpMode();
	bool getIsFlyingUpMode();


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
	int getMomentumLevelToFly();


	// Tail
	int getTailMarginTop();
	int getTailHeight();
	int getTailMarginBottom();

	// Bomb Attack
	int getNumberBombsAttached();

	// Detect component standing on
	int getComponentIdStandingOn();
	int getEndDroppingDownPipe();
	int getEndPoppingUpPipe();



	//
	// =============== Setter ===============
	//
	void setFirstFireBallAnimation(Animation* _animation);
	void setState(MarioState _state);
	void setSubState(MarioSubState _subState);
	void setPressureState(MarioState _pressureState);
	void setPressureAnimation(Animation _animation);
	void setAnimation(Animation* _animation);

	// Control
	void setIsFlip(bool _isFlip);
	void setIsConverting(bool _isConverting);
	void setIsReduceWalking(bool _isReduceWalking);
	void setIsStandOnSurface(bool _isStandOnSurface);
	void setupReduceWalking(bool _isReduceWalking);
	void setIsTurningAround(bool _isTurningAround);
	void setIsPressA(bool _isPressA);
	void setIsPressKeyUp(bool _isPressKeyUp);
	void setIsPressKeyS(bool _isPressKeyS);

	
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
	void turnOnPreFlyingUpSkin();
	void turnOffPreFlyingUpSkin();
	void setIsPreFlyingUpMode(bool _isPreFlyingUpMode);
	void setIsFlyingUpMode(bool _isFlyingUpMode);


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


	// Momentum to fly
	void setMomentumLevel(int _momentumLevel);
	void setMomentum(int _momentum);
	void plusMomentum(int _momentum);

	// Tail
	void setTailMarginTop(int _tailMarginTop);
	void setTailHeight(int _tailHeight);
	void setTailMarginBottom(int _tailMarginBottom);

	// Bomb Attack
	void increaseBombAttached();

	// Detect component standing on
	void setComponentIdStandingOn(int _componentIdStandingOn);




	// Update & Draw
	void updateVelocity(float _dt);
	void Update(float _dt);
	void Draw();

	// Keyboard
	void onKeyUp();
	void onKeyUp(vector<KeyType> _keyTypes);
	void onKeyDown(vector<KeyType> _keyTypes);


	void load();
	void loadInfo(string line, char seperator);
	void save();


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
	void handleCoinCollision(Coin* _coin, float _dt);
	void handlePButtonCollision(PButton* _pButton, float _dt);
	void handleGreenPipeDownCollision(GreenPipe* _greenPipe, int _targetId, float _leftAnchor, float _rightAnchor, float _dt);
	void handleMusicBoxCollision(MusicBox* _musicBox, float _dt);
	void handleBoomerangBroCollision(BoomerangBro* _boomerangBro, float _dt);
	void handleBoomerangCollision(Boomerang* _boomerang, float _dt);
	void handleBossCollision(Boss* _boss, float _dt);
	void handleBombCollision(Bomb* _bomb, float _dt);
	void handleItemCollision(Item* _item, float _dt);
};

#endif // !MARIO_H