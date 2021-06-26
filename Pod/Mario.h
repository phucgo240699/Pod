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
	bool isFlip; // false: Left side - true: Right side. Default is false
	bool debugMode = true;

	Animation* currentAnimation;

	bool isStandOnSurface = false;
	int componentIdStanded;


public:
	float startdrop = 0;
	// Init
	Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);
	Mario(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);

	// Getter
	Animation* getCurrentAnimation();
	MarioSubState getSubState();
	MarioState getState();
	RECT getFrame();
	RECT getBounds();
	bool getIsFlip();
	float getWidth();
	float getHeight();
	bool getIsStandOnSurface();


	// Setter
	void setIsFlip(bool _isFlip);
	void setState(MarioState _state);
	void setSubState(MarioSubState _subState);
	void setIsStandOnSurface(bool _isStandOnSurface);
	void updateVelocity();

	// Inherit
	void Update(float _dt);
	void Draw();

	// Keyboard
	void onKeyUp();
	void onKeyUp(vector<KeyType> _keyTypes);
	void onKeyDown(vector<KeyType> _keyTypes);

	void loadInfo(string line, char seperator);


	void handleGroundCollision(Ground* _ground, float _dt);
	void handleBlockCollision(Block* _block, float _dt);
	void handleGoldenBrickCollision(GoldenBrick* _goldenBrick, float _dt);
	void handleGiftBrickCollision(GiftBrick* _goldenBrick, float _dt);
	void handleGreenPipeCollision(GreenPipe* _greenPipe, float _dt);
	void handleGoombaCollision(Goomba* _goomba, float _dt);
};

#endif // !MARIO_H