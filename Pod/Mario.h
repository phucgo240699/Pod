#pragma once
#include "MarioState.h"
#include "KeyType.h"
#include "Camera.h"
#include "Animation.h"
#include "MainCharacter.h"
#include <unordered_map>
#include <math.h>

using namespace std;

class Mario : public MainCharacter
{
private:
	LPDIRECT3DTEXTURE9 texture;
	MarioState state;
	bool isFlip; // false: Left side - true: Right side. Default is false
	
	vector<Animation*>* animations;
	Animation* currentAnimation;
	float gravity = 1;
	float maxVy = 10;
	float maxVx = 5;

	void setUpAnimations();

public:
	// Init
	Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);
	Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);

	// De Init
	~Mario();

	// Getter
	Animation* getCurrentAnimation();
	MarioState getState();
	RECT* getBounds();
	bool getIsFlip();

	// Setter
	void setIsFlip(bool _isFlip);
	void setState(MarioState _state);
	//void updateCurrentAnimationByState();
	void updateVelocity();

	// Inherit
	void Update(float _dt);
	void Draw();

	// Keyboard
	void onKeyUp();
	void onKeyUp(KeyType _keyType);
	void onKeyDown(KeyType _keyType);
};

