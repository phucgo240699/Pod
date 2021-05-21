#pragma once
#include "MarioState.h"
#include "KeyType.h"
#include "Camera.h"
#include "Animation.h"
#include <unordered_map>

class Mario : public Component
{
private:
	LPDIRECT3DTEXTURE9 texture;
	MarioState state;
	bool isFlip; // false: Left side - true: Right side. Default is false
	
	vector<Animation*>* animations;
	Animation* currentAnimation;

	void setUpAnimations();

public:
	// Init
	Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);
	Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);

	// De Init
	~Mario();

	// Getter
	MarioState getState();
	RECT* getBounds();

	// Setter
	void setState(MarioState _state);
	void updateCurrentAnimation(MarioState _state);

	// Inherit
	void Update(float _dt);
	void Draw();

	// Keyboard
	void onKeyUp();
	void onKeyDown(KeyType _keyType);
};

