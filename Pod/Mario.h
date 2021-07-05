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
//#include "Goomba.h"
#include "Koopa.h"
#include "Block.h"
#include "GreenPipe.h"
#include <unordered_map>

using namespace std;

class Goomba; // Say Mario exists without defining it.

class Mario : public MainCharacter
{
private:
	LPDIRECT3DTEXTURE9 texture;
	MarioState state;
	MarioSubState subState;
	MarioState pressureState; // Hold state of mario before scaling up or scaling down
	Animation* currentAnimation;

	// Control
	bool isStandOnSurface = false, isReduceWalking = false;
	bool isFlip; // false: Left side - true: Right side. Default is false

	// Mode
	bool isSuperMode = false, isFlashMode = false, debugMode = true;

	// Validate Animation
	int oldFrameHeight, oldFrameWidth;
	int newFrameHeight, newFrameWidth;

	// Point
	int pointCoef = 0;
	int countDownFlash = 512;

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
	RECT getBounds();

	float getBoundsWidth();
	float getBoundsHeight();
	float getWidth();
	float getHeight();

	// Control
	bool getIsFlip();
	bool getIsReduceWalking();
	bool getIsStandOnSurface();
	
	// Mode
	bool getIsSuperMode();
	bool getIsFlashMode();

	int getPointCoef();



	//
	// =============== Setter ===============
	//
	void setState(MarioState _state);
	void setSubState(MarioSubState _subState);
	void setPressureState(MarioState _pressureState);

	// Control
	void setIsFlip(bool _isFlip);
	void setIsReduceWalking(bool _isReduceWalking);
	void setIsStandOnSurface(bool _isStandOnSurface);
	
	// Mode
	void setIsSuperMode(bool _isSuperMode);
	void setIsFlashMode(bool _isFlashMode);

	void updateVelocity();
	void increasePointCoef(); // this method will add pointCoeft to 1.
	void resetPointCoef(); // this method will set pointCoef to 0.

	// Inherit
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
	void handleGiftBrickCollision(GiftBrick* _goldenBrick, float _dt);
	void handleGreenPipeCollision(GreenPipe* _greenPipe, float _dt);
	void handleGoombaCollision(Goomba* _goomba, float _dt);
	void handleKoopaCollision(Koopa* _koopa, float _dt);
	void handleSuperMushroomCollision(SuperMushroom* _superMushroom, float _dt);
};

#endif // !MARIO_H