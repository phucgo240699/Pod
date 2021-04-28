#pragma once
#include "MarioState.h"
#include "Keyboard.h"
#include "Camera.h"
#include "MarioStandingLeft.h"
#include <unordered_map>

class Mario : public Component
{
private:
	LPDIRECT3DTEXTURE9 texture;
	MarioState state;
	
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

	// Inherit
	void Update(float _dt);
	void Draw();

	// Keyboard
	void onKeyUp();
	void onKeyDown(KeyType _keyType);
};

