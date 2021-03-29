#pragma once
#include "Component.h"
#include "MarioState.h"
#include "Keyboard.h"

class Mario : public Component
{
private:
	LPDIRECT3DTEXTURE9 texture;
	MarioState state;

	float width, height;
public:
	// Init
	Mario(float _x, float _y, float _vx, float _vy, float _dt, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);
	Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _dt, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);

	// De Init
	~Mario();

	// Getter
	MarioState getState();
	RECT* getBounds();

	// Setter
	void setState(MarioState _state);

	// Inherit
	void Update();
	void Draw();

	// Keyboard
	void onKeyUp();
	void onKeyDown(KeyType _keyType);
};

